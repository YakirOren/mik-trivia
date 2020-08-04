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
    /// Interaction logic for register.xaml
    /// </summary>
    public partial class register : Page
    {
        public register()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {

            MainWindow parentWindow = Window.GetWindow(this) as MainWindow;

            if (parentWindow != null)
            {

                if (parentWindow.Client.signup(name.Text, password.Password, email.Text))
                {
                    this.NavigationService.GoBack();
                }
            }



        }
    }
}
