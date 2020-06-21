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
    /// Interaction logic for login.xaml
    /// </summary>
    public partial class login : Page
    {
        public login()
        {
            InitializeComponent();
        }

        private void register_btn_Click(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new register());
        }

        private void submit_Click(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new join_games());
        }
    }
}
