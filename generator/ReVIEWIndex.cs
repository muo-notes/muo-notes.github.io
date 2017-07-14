using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Text.RegularExpressions;
using System.Linq;

namespace ReVIEWBlog
{

    public class ReVIEWIndex
    {
        class ReVIEWChapter
        {
            public int No;
            public int Kb;
            public int Chars;
            public int Lines;
            public string Title;
            public string Filename;
            public List<ReVIEWSection> Sections = null;
        }

        class ReVIEWSection
        {
            public int Lines;
            public int No;
            public string Title;
        }

        List<ReVIEWChapter> mChapters = null;
        public void Prepare(string dir)
        {
            var psi = Utils.CreateProcessStartInfoAtTargetDirectory(
                dir,
                "review-index",
                $"-a -l 2");
            var p = Process.Start(psi);
            // eliminate \r\n for Windows
            var indexSrc = p.StandardOutput.ReadToEnd().Replace("\r\n", "\n");
            mChapters = this.ParseIndex(indexSrc);
        }

        public string GenerateSimpleHTML(Func<string,string> titleDecorator = null)
        {
            if (mChapters == null)
            {
                throw new InvalidOperationException("Call Prepare(...) before generating output");
            }
            var buf = new StringBuilder();
            buf.Append("<ul class=\"book-toc\">\n");
            foreach (var ch in (mChapters as IEnumerable<ReVIEWChapter>).Reverse())
            {
                var title = titleDecorator != null ? titleDecorator(ch.Title) : ch.Title;
                buf.Append($"<li><a href=\"./{ch.Filename}.html\">{title}</a></li>\n");
                if (ch.Sections.Count == 0)
                {
                    continue;
                }
                buf.Append("<ol>\n");
                foreach (var sec in ch.Sections)
                {
                    buf.Append($"<li>{sec.Title}</li>\n");
                }
                buf.Append("</ol>\n");
            }
            buf.Append(@"</ul>");
            return buf.ToString();
        }

        private List<ReVIEWChapter> ParseIndex(string indexSrc)
        {
            // simple parser
            var rChapter = new Regex(@"^\s*(?<chap_no>\d+).\s*(?<chap_kb>\d+)KB\s*(?<chap_chars>\d+)C\s*(?<chap_lines>\d+)L\s+(?<chap_title>.+)\s*\((?<chap_filename>[^\)]+)\)$");
            var rSection = new Regex(@"^\s*(?<sec_lines>\d+)L\s*(?<sec_no>\d+)\s+(?<sec_title>.+)\s*$");
            var chapters = new List<ReVIEWChapter>();
            ReVIEWChapter currentChapter = null;
            foreach (var line in indexSrc.Split('\n'))
            {
                var m1 = rChapter.Match(line);
                if (m1.Success)
                {
                    var ch = new ReVIEWChapter
                    {
                        No = Int32.Parse(m1.Groups["chap_no"].Value),
                        Kb = Int32.Parse(m1.Groups["chap_kb"].Value),
                        Chars = Int32.Parse(m1.Groups["chap_chars"].Value),
                        Lines = Int32.Parse(m1.Groups["chap_lines"].Value),
                        Title = m1.Groups["chap_title"].Value.Trim(),
                        Filename = m1.Groups["chap_filename"].Value,
                        Sections = new List<ReVIEWSection>(),
                    };
                    chapters.Add(ch);
                    currentChapter = ch;
                    continue;
                }
                var m2 = rSection.Match(line);
                if (m2.Success)
                {
                    var sec = new ReVIEWSection
                    {
                        Lines = Int32.Parse(m2.Groups["sec_lines"].Value),
                        No = Int32.Parse(m2.Groups["sec_no"].Value),
                        Title = m2.Groups["sec_title"].Value,
                    };
                    currentChapter?.Sections.Add(sec);
                }
            }
            return chapters;
        }
    }

}