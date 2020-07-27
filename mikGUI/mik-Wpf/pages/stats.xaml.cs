using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace mik_Wpf
{
    /// <summary>
    /// Interaction logic for stats.xaml
    /// </summary>
    public partial class stats : Window
    {
        public MainWindow parentWindow;
        public stats()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            MainWindow mainWindow = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();

            try
            {
                var a = mainWindow.Client.getStats();
                if (mainWindow != null)
                {
                    this.AvgAnswerTime.Content += " " + a[1];
                    this.TotalCorrectAnswers.Content += " " + a[2];
                    this.TotalAnswers.Content += " " + a[3];
                    this.TotalPlayedGames.Content += " " + a[4];

                }
            }
            catch (Exception gay)
            {

                Console.WriteLine(gay.Message);
            }
            //mainWindow.Client.CreateRoom("2");


        }
    }
}
