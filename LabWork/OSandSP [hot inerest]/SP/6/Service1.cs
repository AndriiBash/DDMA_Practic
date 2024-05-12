using System.ServiceProcess;
using System.Threading;

namespace WindowsMyService
{    
    public partial class Service1 : ServiceBase
    {
        private TimeLogger logger;
        public Service1()
        {
            InitializeComponent();
        }
        protected override void OnStart(string[] args)
        {
            logger = new TimeLogger();
            Thread loggerThread = new Thread(new ThreadStart(logger.Start));
            loggerThread.Start();
        }
        protected override void OnStop()
        {
            logger.Stop();
        }
    }
}
