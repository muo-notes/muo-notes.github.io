using System;
using System.IO;
using DotLiquid;
using DotLiquid.Tags;

class Program
{
    static void Main(string[] args)
    {
        var template = Template.Parse(File.ReadAllText("templates/entry.html"));
        var result = template.Render(Hash.FromAnonymousObject(new {
            title = "foobar",
            postedAt = DateTime.Now,
            post = "foobarbody",
            keywords = new[] {"foo", "bar"}
        }));
        Console.WriteLine(result);
    }
}
