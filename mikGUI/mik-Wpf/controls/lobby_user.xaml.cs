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
    /// Interaction logic for user_lobby.xaml
    /// </summary>
    public partial class lobby_user : UserControl
    {
        public lobby_user()
        {
            InitializeComponent();
        }

        public lobby_user(string name)
        {
            InitializeComponent();
            this.player.Text = name;
        }


    }
}
