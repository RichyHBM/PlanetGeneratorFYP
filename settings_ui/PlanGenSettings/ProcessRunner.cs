using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.IO;

namespace PlanGenSettings
{
    class ProcessRunner
    {
        String executable;
        String processName;
        StreamWriter writer;

        public ProcessRunner(String name)
        {
            processName = name;
            int pID = (int)Environment.OSVersion.Platform;
            if ((pID == 4) || (pID == 6) || (pID == 128))
            {
                //Unix
                executable = "./" + name;
            }
            else
            {
                //Windows
                executable = "./" + name + ".exe";
            }
        }

        public void CallAndLog(String[] arguments)
        {
            String argument = String.Empty;
            if (arguments != null)
            {
                foreach (String arg in arguments)
                {
                    argument += arg + " ";
                }
            }

            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.FileName = executable;
            startInfo.Arguments = argument;
            startInfo.RedirectStandardOutput = true;
            startInfo.UseShellExecute = false;

            using (writer = new StreamWriter(processName + ".txt"))
            {
                Process process = new Process();
                process.StartInfo = startInfo;
                process.OutputDataReceived += OutputDataReceived;

                process.Start();
                process.BeginOutputReadLine();
                process.WaitForExit();
            }

        }

        private void OutputDataReceived(object sender, DataReceivedEventArgs e)
        {
            Console.WriteLine(e.Data);
            writer.WriteLine(e.Data);
        }
    }
}
