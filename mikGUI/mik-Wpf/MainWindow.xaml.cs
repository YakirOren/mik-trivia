﻿
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

using System.Net.Sockets;
using System.Net;

using mik_Wpf.app_code;

namespace mik_Wpf
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public string username = "";
        public socket_client Client;
        
        public MainWindow()
        {
            InitializeComponent();

            Client = new socket_client("127.0.0.1", 6969);

            _mainFrame.Navigate(new login());

        }


    }
}
