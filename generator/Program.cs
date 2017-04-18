using System;
using System.IO;
using DotLiquid;
using DotLiquid.Tags;

class Program
{
    const int REVIEW_COMPILE_TIMEOUT_MS = 30000;

    static void RenderTemplate(string templatePath, DotLiquid.Hash hashObj, string outputPath)
    {
        var template = Template.Parse(File.ReadAllText(templatePath));
        var result = template.Render(hashObj);
        File.WriteAllText(outputPath, result);
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
                RenderTemplate(
                    Path.Combine("templates", "index.html"),
                    Hash.FromAnonymousObject(new { content = indexContent, postedAt = DateTime.Now }),
                    Path.Combine("..", "index.html"));
            }
            else
            {
                var reviewFilename = args[0];
                Console.WriteLine("target: " + reviewFilename);
                conv.CompileDocument(reviewFilename, REVIEW_COMPILE_TIMEOUT_MS);
                var decoratedContent = conv.DecorateForBlog("foobar");
                var entry = conv.ExtractTitleAndContent();
                RenderTemplate(
                    Path.Combine("templates", "entry.html"),
                    Hash.FromAnonymousObject(new
                    {
                        title = entry.title,
                        postedAt = DateTime.Now,
                        post = entry.body,
                        keywords = new[] { "foo", "bar" }
                    }),
                    Path.Combine("..", reviewFilename.Replace(".re", ".html")));
            }
        }
    }
}
