using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Drawing;
using System.Diagnostics;

namespace Shell
{
    public partial class MainWindow : Form
    {
        public MainWindow()
        {
            InitializeComponent();
            MainWindow_MouseLeave(this, null);
        }

        // Запуск процесса
        private void Start(string proc, string exec)
        {
            try
            {
                Process.Start(proc, exec);
            }
            catch (System.Exception ex)
            {
                string err = "Произошла ошибка";
                MessageBox.Show(err + ":\r\n" + ex.Message + "\r\n" + proc, err);
            }
        }

        // Запуск подпрограмм
        private void BtnRegistrator_Click(object sender, EventArgs e)
        {
            Start("Registrator", "");
        }
        private void BtnArchive_Click(object sender, EventArgs e)
        {
            Start("Processor", "\"" + Application.StartupPath + "\\Archive.mdb\"");
        }
        private void BtnAnalysis_Click(object sender, EventArgs e)
        {
            Start("MatLAB", "-minimize -r \"open Analisys.fig\"");
        }

        // Дополнительные материалы
        private void BtnHelp_Click(object sender, EventArgs e)
        {
            Start("WinWord", "\"" + Application.StartupPath + "\\Help.doc\"");
        }
        private void BtnAbout_Click(object sender, EventArgs e)
        {
            MessageBox.Show(
                "Программа разработана фирмой Бригада №6\r\n" +
                "студенты: Сусак Н., Усков М., Филатова Ю.\r\n" +
                "По заказу МЭИ(ТУ) в 2011 году.\r\n\r\n" +
                "За более подробной информацией обращаться\r\n" +
                "в раздел \"Помощь\"", "О программе");
        }
        private void BtnExit_Click(object sender, EventArgs e)
        {
            Close();
        }
        
        // Перемещения формы
        private void MainWindow_MouseDown(object sender, MouseEventArgs e)
        {
            drugStart = e.Location;
            drugProcess = true;
        }
        private void MainWindow_MouseMove(object sender, MouseEventArgs e)
        {
            if (!drugProcess)
                return;
            
            int x = Location.X + e.Location.X - drugStart.X;
            int y = Location.Y + e.Location.Y - drugStart.Y;
            Location = new Point(x, y);
        }
        private void MainWindow_MouseUp(object sender, MouseEventArgs e)
        {
            drugProcess = false;
        }
        private Point drugStart;
        private bool drugProcess = false;

        // Расширение при наведении
        int baseSx, baseSy;
        private void MainWindow_MouseEnter(object sender, EventArgs e)
        {
            TimerHide.Stop();
            Size size = new Size(baseSx, baseSy);
            MaximumSize = size;
            MinimumSize = size;
            Size = size;
        }
        private void MainWindow_MouseLeave(object sender, EventArgs e)
        {
            TimerHide.Start();
        }

        // Таймер
        private void TimerHide_Tick(object sender, EventArgs e)
        {
            Size size = new Size(baseSx, (int)(baseSy * 0.41));
            MaximumSize = size;
            MinimumSize = size;
            Size = size;
        }
        private void MainWindow_Load(object sender, EventArgs e)
        {
            baseSx = this.Size.Width;
            baseSy = this.Size.Height;
        }

    }
}
