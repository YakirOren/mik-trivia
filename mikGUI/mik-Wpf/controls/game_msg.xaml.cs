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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace mik_Wpf
{
    /// <summary>
    /// Interaction logic for game.xaml
    /// </summary>
    public partial class game_msg : UserControl
    {
        public int MaxPlayers { get; set; }
        public int players { get; set; }
        public string driver { get; set; }
        public string destination { get; set; }
        public int ID { get; set; }

        private MainWindow MainWindow;

        public game_msg()
        {
            InitializeComponent();
        }

        public void AddPlayer()
        {
            players++;
            this.players_lbl.Text = string.Format("{0}/{1}", players, MaxPlayers);
        }

        public game_msg(int players, string driver)
        {
            InitializeComponent();
            
            MaxPlayers = 4;
            this.driver = driver;
            this.players_lbl.Text = string.Format("{0}/{1}", players, MaxPlayers);
            
            this.driver_lbl.Text = driver;
            this.destination_lbl.Text = "מיקפה";
        }

        private void join_Click(object sender, RoutedEventArgs e)
        {
            AddPlayer();
            
            if (this.MainWindow != null)
            {

                //send JoinRoomRequest
                if (true)
                {
                    var dd = new create_texi(ID);
                    this.MainWindow.Hide();
                    dd.ShowDialog();
                    this.MainWindow.Show();
                }

            }

        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            this.MainWindow = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
        }
    }
}
