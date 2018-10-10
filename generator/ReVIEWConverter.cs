using System;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Xml.Linq;
using CenterCLR.Sgml;
using System.Linq;
using System.Runtime.InteropServices;
using SixLabors.ImageSharp;
using System.Collections.Generic;
using System.Text.RegularExpressions;

namespace ReVIEWBlog
{

    public class ReVIEWConverter
    {
        const int DEFAULT_TIMEOUT_MS = 30000;
        XDocument innerDocument;

        public string CompileDocument(string filename, int timeoutMilliSec = DEFAULT_TIMEOUT_MS)
        {
            var psi = Utils.CreateProcessStartInfoAtTargetDirectory(
                Path.GetDirectoryName(Path.GetFullPath(filename)),
                "review-compile",
                $"--target=html {Path.GetFileName(filename)}");
            var p = Process.Start(psi);
            var content = p.StandardOutput.ReadToEnd().Replace("\r\n", "\n");
            // TODO: also handle StandardError
            p.WaitForExit(timeoutMilliSec);

            using (var st = new MemoryStream(Encoding.UTF8.GetBytes(content)))
            {
                this.innerDocument = SgmlReader.Parse(st);
            }

            return content;
        }

        public string GenerateIndex(string dir)
        {
            var idx = new ReVIEWIndex();
            idx.Prepare(dir);
            return idx.GenerateSimpleHTML(titleDecorator: s => SeparateKeywordsFromTitle(s).subject);
        }

        public XDocument DecorateForBlog(string idPrefix)
        {
            var doc = this.innerDocument;
            var ns = doc.Root.Name.Namespace;
            XNamespace epubNs = "http://www.idpf.org/2007/ops";

            foreach (var el in doc.Descendants(ns + "a"))
            {
                // make footnote ids unique
                if (el.Attribute("class") != null)
                {
                    var className = el.Attribute("class").Value;
                    if (className == "noteref" || className == "footnote")
                    {
                        if (el.Attribute("id") == null)
                        {
                            throw new InvalidOperationException("footnotes/note references without `id` attribute should never appear.");
                        }
                        el.Attribute("id").Value = idPrefix + el.Attribute("id").Value;
                    }
                }
                // cleanup epub attributes
                if (el.Attribute(epubNs + "type") != null)
                {
                    el.Attribute(epubNs + "type").Remove();
                }
            }

            foreach (var el in doc.Descendants(ns + "div").Where(
                o => o.Attribute("class") != null ? o.Attribute("class").Value == "footnote" : false))
            {
                el.Attribute("id").Value = idPrefix + el.Attribute("id").Value;
                // cleanup epub attributes
                if (el.Attribute(epubNs + "type") != null)
                {
                    el.Attribute(epubNs + "type").Remove();
                }
            }
            foreach (var el in doc.Descendants(ns + "img").ToList())
            {
                var imgName = el.Attribute("src").Value;
                if (!File.Exists(imgName))
                {
                    continue;
                }
                using (var img = Image.Load(imgName))
                {
                    var ampImg = new XElement(
                            ns + "amp-img",
                            new XAttribute("src", "articles/" + imgName),
                            new XAttribute("width", img.Width),
                            new XAttribute("height", img.Height),
                            new XAttribute("layout", "responsive"));
                    el.ReplaceWith(ampImg);
                }
            }
            return doc;
        }

        (string subject, List<string> keywords) SeparateKeywordsFromTitle(string originalTitle)
        {
            if (!originalTitle.Contains("#"))
            {
                return (originalTitle, new List<string>());
            }
            const string keywordPattern = "#\\S+";
            var matches = Regex.Matches(originalTitle, keywordPattern);
            var keywords = new List<string>();
            foreach (Match m in matches)
            {
                keywords.Add(m.Value.Substring(1));
            }
            // trim trailing tags only (keep tags found in this manner: "#tag is great")
            // so, "#tag is great #foo #bar #baz" -> "#tag is great"
            string subjectCandidate = originalTitle.Trim();
            string prevCandidate = string.Empty;
            while (prevCandidate.Length < subjectCandidate.Length)
            {
                prevCandidate = subjectCandidate;
                subjectCandidate = Regex.Replace(subjectCandidate, "\\s*#\\S+$", "");
            }
            return (subjectCandidate, keywords);
        }
        public (string title, List<string> keywords, string body) ExtractTitleAndContent()
        {
            // create a copy of XDocument to prevent original one from disruptive changes.
            var doc = new XDocument(this.innerDocument);

            var ns = doc.Root.Name.Namespace;
            var h1 = doc.Descendants(ns + "h1").First();
            var title = SeparateKeywordsFromTitle(h1.Value);
            h1.Remove();
            var keywords = new List<string>();
            // TODO: find out somehow better way to perform `InnerXml` thingy w/o placing tons of `xmlns="..."` attributes.
            var bodyContent = doc.Descendants(ns + "body").First().ToString();
            // <body xmlns="http://www.w3.org/1999/xhtml">\n\n <- 45 chars
            // .... <- content
            // </body> <- 7 chars
            var content = bodyContent.Substring(45, bodyContent.Length - 45 - 7);
            return (title.subject, title.keywords, content);
        }
    }

}
