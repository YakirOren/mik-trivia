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
    public partial class game : UserControl
    {
        public int MaxPlayers { get; set; }
        public int players { get; set; }
        public string driver { get; set; }
        public string destination { get; set; }


        public game()
        {
            InitializeComponent();
        }

        public void addPlayer()
        {
            this.players_lbl.Text = driver;
        }

        public game(int players, string driver, string destination)
        {
            InitializeComponent();
            MaxPlayers = 4;
            this.players_lbl.Text = string.Format("{0}/{1}", players, MaxPlayers);
            this.driver_lbl.Text = driver;
            this.destination_lbl.Text = destination;
        }

    }
}
