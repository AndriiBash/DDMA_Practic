using System;
using System.Timers;

namespace WindowsMyService
{
    class TimeLogger
    {
        System.Timers.Timer timer;
     
        public void Start()
        {
            timer = new Timer(1000);
            timer.Elapsed += this.Log;
            timer.Start();
        }
        
        public void Stop()
        {
            timer.Stop();
        }       
        private void Log(Object source, ElapsedEventArgs e)
        {
            using (System.IO.StreamWriter file = new System.IO.StreamWriter(@"C:\Test.txt", true))
            {
                file.WriteLine(DateTime.Now.ToString());
            }
        }
    }
}
