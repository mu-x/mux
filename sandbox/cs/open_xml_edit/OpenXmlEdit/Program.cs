using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace OpenXmlEdit
{
    static class Program
    {
        /// <summary>
        /// Главная точка входа для приложения.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new WinMain(args));
        }
    }
}
