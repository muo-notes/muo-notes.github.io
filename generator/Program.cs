using System;
using System.IO;
using DotLiquid;
using DotLiquid.Tags;

class Program
{
    const int REVIEW_COMPILE_TIMEOUT_MS = 30000;

    static void Main(string[] args)
    {
        var reviewFilename = args[0];
        Console.WriteLine("target: " + reviewFilename);
        var conv = new ReVIEWConverter();
        conv.CompileDocument(reviewFilename, REVIEW_COMPILE_TIMEOUT_MS);
        var decoratedContent = conv.DecorateForBlog("foobar");
        var entry = conv.ExtractTitleAndContent();
        var template = Template.Parse(File.ReadAllText("templates/entry.html"));
        var result = template.Render(Hash.FromAnonymousObject(new {
            title = entry.title,
            postedAt = DateTime.Now,
            post = entry.body,
            keywords = new[] {"foo", "bar"}
        }));
        File.WriteAllText(Path.Combine("..", reviewFilename.Replace(".re", ".html")), result);
    }
}
