using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace OpenXmlEdit
{
    public enum InOutTypes
    {
        Text = 1,
        Check
    }

    static class InOutBox
    {

    #region Система логирования сообщений
        // Лог-файл
        private static StreamWriter log = null;
        private static bool logOn = false;

        // Создание лог-файла
        public static void StartLog()
        {
            StartLog(Application.StartupPath, "Log", ".log", true);
        }
        public static void StartLog(string path, string prefix, string ext, bool on)
        {
            log = new StreamWriter(path + "\\" + prefix +
                DateTime.Now.ToString("yyyy-MM-dd hh.mm.ss") +
                ext, false);
            logOn = on;
            Log("Запуск системы логрования");
        }

        // Запись в лог
        public static void Log(string text)
        {
            if (log == null)
                return;

            log.WriteLine(DateTime.Now.ToString("yyyy-MM-dd hh.mm.ss"));
            log.WriteLine("  " + text.Replace("\r\n", "\r\n  ") + "\r\n");
            log.Flush();
        }

        // Закрытие лога
        public static void EndLog()
        {
            Log("Завершение логирования");
            log.Close();
            log = null;
        }
    #endregion

    #region Вывод сообщений типа MessageBox
        // Вывод информационного сообщения
        public static DialogResult Message(string title, string text)
        {
            if (logOn)
                Log("Сообщение: " + title + "\r\n" + text);
            return MessageBox.Show(text, title,
                MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        // Сообщение об ошибке (появлениии исключения)
        public static DialogResult Error(string title, Exception ex)
        {
            if (logOn)
                Log("Ошибка: " + title + "\r\n" + ex.Message);
            return MessageBox.Show(title + ":\r\n\r\n" + ex.Message, title,
                MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        // Вопрос (Да, Нет, ...)
        public static DialogResult Question(string title, string text)
        {
            return Question(title, text, MessageBoxButtons.YesNo);
        }
        public static DialogResult Question(string title, string text,
            MessageBoxButtons btn)
        {
            if (logOn)
                Log("Запрос: " + title + "\r\n" + text);
            DialogResult res = MessageBox.Show(text, title,
                btn, MessageBoxIcon.Question);
            if (logOn)
                Log("Ответ: " + res.ToString());
            return res;
        }
    #endregion

    #region Вывод сообщений типа InputBox
        private static bool inputOk = false;

        // Звпрос 1го строкового параметра
        public static DialogResult Input(string title, string text,
            ref string values)
        {
            string[] arr = { values };
            DialogResult res = Input(title, new string[] { text }, ref arr);

            values = arr[0];
            return res;
        }

        // Запрос N строковых параметров
        public static DialogResult Input(string title, string[] text,
            ref string[] values)
        {
            InOutTypes[] types = new InOutTypes[text.Length];
            for (int i = 0; i < text.Length; ++i)
                types[i] = InOutTypes.Text;

            return Input(title, text, types, ref values);
        }

        // Запрос N параметров разных типов
        public static DialogResult Input(string title, string[] text,
            InOutTypes[] types, ref string[] values)
        {
            int count = text.Length;
            if ((count != types.Length) || (count > values.Length))
                throw new Exception("Размеры массивов не совпадают.");

            // Размеры:
            int border = 10;
            int shortInt = 25;
            int longInt = 55;
            int width = 200;
            int button = 80;

            var form = new Form();
            form.Text = title;
            form.StartPosition = FormStartPosition.CenterScreen;
            form.Size = new Size(border + width + border * 2,
                border + count * longInt + longInt + border);
            form.FormBorderStyle = FormBorderStyle.Fixed3D;
            form.MaximizeBox = false;
            form.MinimizeBox = false;
            form.ShowIcon = false;

            var labels = new Label[count];
            for (int i = 0; i < count; i++)
            {
                labels[i] = new Label();
                labels[i].Text = text[i];
                labels[i].Width = width;
                labels[i].Location = new Point(border, border + i * longInt);
                form.Controls.Add(labels[i]);
            }

            // За счёт разных типов параметров
            // все поля типизируются как контролы
            var boxes = new Control[count];
            for (int i = 0; i < count; i++)
            {
                switch (types[i])
                {
                    case InOutTypes.Text: boxes[i] = new TextBox(); break;
                }

                boxes[i].Text = values[i];
                boxes[i].Location = new Point(border,
                    border + i * longInt + shortInt);
                boxes[i].Width = width;
                boxes[i].RightToLeft = RightToLeft.Yes;
                form.Controls.Add(boxes[i]);
            }

            var btnOk = new Button();
            btnOk.Text = "ОК";
            btnOk.Width = button;
            btnOk.Location = new Point(width - button * 2,
                border + count * longInt);
            btnOk.Click += new EventHandler(btnOkClick);
            form.Controls.Add(btnOk);

            var btnClose = new Button();
            btnClose.Text = "Отмена";
            btnClose.Width = button;
            btnClose.Location = new Point(border + width - button,
                border + count * longInt);
            btnClose.Click += new EventHandler(btnOkClick);
            form.Controls.Add(btnClose);

            inputOk = false;
            form.ShowDialog();

            // Флажок "inputOk" не потокозащищён, хотя ИМХО
            // кликать "ок" и "отмена" в двух окнах одновременно
            // весьма трудоёмко для пользователя (=
            if (inputOk)
            {
                for (int i = 0; i < count; i++)
                    values[i] = boxes[i].Text;

                inputOk = false;
                return DialogResult.OK;
            }

            return DialogResult.Cancel;
        }

        // Действия кнопок запроса
        private static void btnOkClick(object sender, EventArgs e)
        {
            ((Form)((Control)sender).Parent).Close();
            inputOk = true;
        }
        private static void btnCloseClick(object sender, EventArgs e)
        {
            ((Form)((Control)sender).Parent).Close();
            inputOk = false;
        }
    #endregion

    }
}
