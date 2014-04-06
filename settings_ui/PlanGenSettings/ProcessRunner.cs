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
        StreamWriter writer = null;

        public ProcessRunner(String name)
        {
            processName = name;
            int pID = (int)Environment.OSVersion.Platform;
            if ((pID == 4) || (pID == 6) || (pID == 128))
            {
                //Unix
                executable = "./" + name;
            } else
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

            try
            {
                writer = new StreamWriter(string.Format("{0}-{1:yyyy-MM-dd_hh-mm-ss-tt}.txt", processName, DateTime.Now));
            } catch (Exception e)
            {

            }

			try
            {
				Process process = new Process();
				process.StartInfo = startInfo;
				process.OutputDataReceived += OutputDataReceived;

				process.Start();
				process.BeginOutputReadLine();
				process.WaitForExit();
			} catch (Exception e)
            {

            }

            if (writer != null)
                writer.Close();

        }

        private void OutputDataReceived(object sender, DataReceivedEventArgs e)
        {
            Console.WriteLine(e.Data);
            if (writer != null){
				try
				{
					writer.WriteLine(e.Data);
				} catch (Exception e)
				{

				}
			}
        }
    }
}
