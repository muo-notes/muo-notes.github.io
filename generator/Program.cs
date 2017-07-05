using System;
using System.IO;
using DotLiquid;
using DotLiquid.Tags;
using CenterCLR.Sgml;
using System.Text;
using System.Linq;
using Newtonsoft.Json;
using System.Collections.Generic;

class Program
{
    const int REVIEW_COMPILE_TIMEOUT_MS = 30000;
    const string BLOG_BASE_URI = "https://notes.muo.jp/";

    static void RenderTemplate(string templatePath, DotLiquid.Hash hashObj, string outputPath)
    {
        var template = Template.Parse(File.ReadAllText(templatePath));
        var result = template.Render(hashObj);
        File.WriteAllText(outputPath, result);
    }

    static string RetrieveLdJsonAttribute(string filePath, string key)
    {
        if (!(File.Exists(filePath)))
        {
            return null;
        }
        using (var st = new MemoryStream(File.ReadAllBytes(filePath)))
        {
            var doc = SgmlReader.Parse(st);
            var ns = doc.Root.Name.Namespace;
            var ldJsonElement = doc.Descendants(ns + "script")
                .Where(o => o.Attribute("type") != null && o.Attribute("type").Value == "application/ld+json")
                .FirstOrDefault();
            if (ldJsonElement == null)
            {
                return null;
            }
            // emblacing "obj" is workaround for translating non-single root JSON data into XNode
            var jsonXObj = JsonConvert.DeserializeXNode($"{{\"obj\": {ldJsonElement.Value} }}");
            var foundNode = jsonXObj.Descendants(key).FirstOrDefault();
            if (foundNode == null)
            {
                return null;
            }
            return foundNode.Value;
        }
    }

    static void Main(string[] args)
    {
        if (args.Length != 0)
        {
            var conv = new ReVIEWConverter();
            if (args[0] == "index")
            {
                Console.WriteLine("Updating index file");
                var indexContent = conv.GenerateIndex(System.IO.Directory.GetCurrentDirectory());
                var pagePath = Path.Combine("..", "index.html");
                var modifiedAt = DateTime.UtcNow;
                var publishedAt = modifiedAt;
                if (File.Exists(pagePath))
                {
                    var p = DateTime.Parse(RetrieveLdJsonAttribute(pagePath, "datePublished"));
                    publishedAt = p.ToUniversalTime();
                }
                var renderContent = new { content = indexContent, publishedAt = publishedAt, modifiedAt = modifiedAt, title = "muo notes" };
                RenderTemplate(
                    Path.Combine("templates", "index.html"),
                    Hash.FromAnonymousObject(renderContent),
                    pagePath);
            }
            else
            {
                var reviewFilename = args[0];
                Console.WriteLine("target: " + reviewFilename);
                conv.CompileDocument(reviewFilename, REVIEW_COMPILE_TIMEOUT_MS);
                var decoratedContent = conv.DecorateForBlog("foobar");
                var entry = conv.ExtractTitleAndContent();
                var pageFilename = reviewFilename.Replace(".re", ".html");
                var pagePath = Path.Combine("..", pageFilename);
                var publishedAt = DateTime.UtcNow;
                var modifiedAt = publishedAt;
                if (File.Exists(pagePath))
                {
                    var p = DateTime.Parse(RetrieveLdJsonAttribute(pagePath, "datePublished"));
                    publishedAt = p.ToUniversalTime();
                }
                RenderTemplate(
                    Path.Combine("templates", "entry.html"),
                    Hash.FromAnonymousObject(new
                    {
                        title = entry.title,
                        publishedAt = publishedAt,
                        modifiedAt = modifiedAt,
                        post = entry.body,
                        keywords = entry.keywords,
                        canonicalUri = $"{BLOG_BASE_URI}{pageFilename}"
                    }),
                    pagePath);
            }
        }
    }
}
