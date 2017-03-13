using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace HiddenAlarm
{
    public partial class FormAlarm : Form
    {
        // Члены класса
        #region Class Members

            Timer timer = new Timer();
            string configFile = Application.StartupPath + "\\HiddenAlarm.conf";

            public FormAlarm()
            {
                InitializeComponent();
                LoadConfigFile();
                timer.Interval = 1000;
                timer.Tick += new System.EventHandler(timer_Tick);
            }

        #endregion

        // Допольнительные функции
        #region Functions Adds

            private int DtToSec(DateTime time)
            {     
                return Convert.ToInt32(Math.Floor(time.TimeOfDay.TotalSeconds));
            }

            private int DtToSec()
            {
                return DtToSec(DateTime.Now);
            }

            private bool confTrackList_ChackFiles()
            {
                List<int> del = new List<int>();
                for (int i = 0; i < confTrackList.Items.Count; ++i)
                    if (!File.Exists(confTrackList.Items[i].ToString()))
                        del.Add(i);
                
                for (int i = del.Count - 1; i >= 0; --i)
                    confTrackList.Items.RemoveAt(del[i]);
                return (confTrackList.Items.Count == 0);
            }

            private void MessageLabel(string msg)
            {
                statusLabel.Text = msg;
            }

            private DialogResult MessageError(string msg)
            {
                MessageLabel(msg);
                return MessageBox.Show(msg, "Ошибка",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        #endregion

        // Удобство галочек
        #region CheckBoxes Visible

            private void timeRepeatBox_CheckedChanged(object sender, EventArgs e)
            {
                timeRepeat.Enabled = timeRepeatBox.Checked;
            }

            private void timeStopBox_CheckedChanged(object sender, EventArgs e)
            {
                timeStop.Enabled = timeStopBox.Checked;
            }

        #endregion

        // Выбор файлов
        #region File Add, Edit, Delete

            private void confPlayerBtn_Click(object sender, EventArgs e)
            {
                OpenFileDialog dialog = new OpenFileDialog();
                dialog.FileName = confPlayer.Text;
                dialog.Filter = "Программа-плеер (*.exe)|*.exe";
                
                if (dialog.ShowDialog() == DialogResult.Cancel)
                    return;
                    
                confPlayer.Text = dialog.FileName;
                string[] buf = dialog.FileName.Split('\\');
                MessageLabel("Выбран плеер '" + buf[buf.Length - 1] + "'");
            }

            private void trackAddBtn_Click(object sender, EventArgs e)
            {
                OpenFileDialog dialog = new OpenFileDialog();
                dialog.Filter = "Звуковой файл (*.*)|*.*";
                
                if (dialog.ShowDialog() == DialogResult.Cancel)
                    return;
                
                confTrackList.Items.Add(dialog.FileName);
                string[] buf = dialog.FileName.Split('\\');
                MessageLabel("Добавлен трэк '" + buf[buf.Length - 1] + "'");
            }

            private void trackDelBtn_Click(object sender, EventArgs e)
            {
                string[] buf = confTrackList.SelectedItem.ToString().Split('\\');
                MessageLabel("Убран трэк '" + buf[buf.Length - 1] + "'");

                if (confTrackList.SelectedIndex != 0)
                    confTrackList.Items.RemoveAt(confTrackList.SelectedIndex);
            }

        #endregion

        // Функциональные клавиши
        #region Functional Buttons

            private void timeStartBtn_Click(object sender, EventArgs e)
            {
                if (confTrackList_ChackFiles())
                {
                    MessageError("Будильник не запущен, список треков пуст!");
                    return;
                }

                MessageLabel("Будильник запущен...");
                ShowInTaskbar = false;
                SaveConfigFile();
                timer.Start();
            }

            private void confTestBtn_Click(object sender, EventArgs e)
            {
                if (confTrackList_ChackFiles())
                {
                    MessageError("Список треков пуст!");
                    return;
                }

                MessageLabel("Проверка плеера запущена...");
                int idx = (new Random(Convert.ToInt32(DateTime.Now.Ticks % 1024000))).
                    Next(confTrackList.Items.Count - 1);
                string args = '"' + confTrackList.Items[idx].ToString() + '"';
                Process.Start(confPlayer.Text, args);
            }

            private void timer_Tick(object sender, EventArgs e)
            {
                Hide();
                if ((timeStopBox.Checked) && (DtToSec(timeStop.Value) != DtToSec()))
                    timer.Stop();
            
                 if (DtToSec(timeStart.Value) != DtToSec())
                    return;

                confTestBtn_Click(this, e);
                if (timeRepeatBox.Checked)
                    timeStart.Value += timeRepeat.Value.TimeOfDay;
            }

            private void FormAlarm_FormClosing(object sender, FormClosingEventArgs e)
            {
                SaveConfigFile();
            }

        #endregion

        // Загрузка, сохранение конфигураци
        #region Configuration Load, Save

            private void LoadConfigFile()
            {
                try
                {
                    StreamReader text = new StreamReader(configFile);
                    string[] line = text.ReadLine().Split('\t');
                    
                    timeStart.Value = Convert.ToDateTime(line[0]);
                    timeRepeatBox.Checked = Convert.ToBoolean(line[1]);
                    timeRepeat.Value = Convert.ToDateTime(line[2]);
                    timeStopBox.Checked = Convert.ToBoolean(line[3]);
                    timeStop.Value = Convert.ToDateTime(line[4]);
                    confPlayer.Text = text.ReadLine();

                    confTrackList.Items.Clear();
                    try {
                        while ((line[0] = text.ReadLine()) != "")
                            confTrackList.Items.Add(line[0]);
                    } catch (Exception e) {};
                    MessageLabel("Конфигурация загружена");
                    text.Close();
                }
                catch (Exception e)
                {
                    SaveConfigFile();
                    MessageLabel("Сохранена конфигурация по умолчанию");
                }
            }

            private void SaveConfigFile()
            {
                confTrackList_ChackFiles();

                StreamWriter text = new StreamWriter(configFile, false);
                text.WriteLine(timeStart.Value.ToString() + "\t" +
                    timeRepeatBox.Checked.ToString() + "\t" +
                    timeRepeat.Value.ToString() + "\t" +
                    timeStopBox.Checked.ToString() + "\t" +
                    timeStop.Value.ToString());
                text.WriteLine(confPlayer.Text);
                
                foreach(object it in confTrackList.Items)
                    text.WriteLine(it.ToString());
                MessageLabel("Конфигурация сохранена");
                text.Close();
            }

        #endregion      
    }
}
