using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Threading;

namespace mik_Wpf
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            var bootStrapper = new BootStrapper();
            bootStrapper.Start();
            base.OnStartup(e);
        }

    }
    public class BootStrapper
    {
        SplashScreen Splash = new SplashScreen();
        MainWindow MainWindow = new MainWindow();

        public void Start()
        {
            var timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(0);
            timer.Tick += (s, e) =>
            {
                Splash.Close();
                MainWindow.Show();
                timer.Stop();
            };

            timer.Start();
            Splash.Show();
        }
    }
}
