using System.Diagnostics;
using System.Runtime.InteropServices;

namespace ReVIEWBlog
{
    class Utils
    {
        public static ProcessStartInfo CreateProcessStartInfoAtTargetDirectory(string dirname, string cmd, string args)
        {
            var psi = new ProcessStartInfo
            {
                WorkingDirectory = dirname,
                RedirectStandardOutput = true
            };
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
            {
                psi.FileName = "cmd.exe";
                psi.Arguments = $"/C {cmd} {args}";
            }
            else
            {
                psi.FileName = cmd;
                psi.Arguments = args;
            }
            return psi;
        }
    }
}