using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.Odbc;
using System.Drawing;
using System.Drawing.Printing;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace Processor
{
    public partial class MainWindow : Form
    {
        // Экземпляр формы фильтра
        FilterWindow filter;

        // Подключение к файлу базы
        OdbcConnection dataBase = new OdbcConnection(
                "Driver={Microsoft Access Driver (*.mdb)};" +
                "Dbq=" + Application.StartupPath + "\\Archive.mdb;" +
                "Uid=admin;Pwd=");

        // Стандарт запросов
        string dataQuery = "SELECT Сессии.Оператор, Сессии.Дата, Кадры.К01 As [Канал 1], Кадры.К02 As [Канал 2], Кадры.К03 As [Канал 3], Кадры.К04 As [Канал 4], Кадры.К05 As [Канал 5], Кадры.К06C As [Среднее 6], Кадры.К06Д As [Дисперсия 6], Кадры.К09 As [Канал 9], Кадры.К16 As [Канал 16], Кадры.К46 As [Канал 46], Кадры.К66 As [Канал 66], Кадры.К76 As [Канал 76] FROM Сессии INNER JOIN Кадры ON Сессии.Номер = Кадры.Сессия";
        string avgQuery = "SELECT '-' As [Оператор], '-' As [Дата], Avg(Кадры.К01) AS [Канал 1], Avg(Кадры.К02) AS [Канал 2], Avg(Кадры.К03) AS [Канал 3], Avg(Кадры.К04) AS [Канал 4], Avg(Кадры.К05) AS [Канал 5], Avg(Кадры.К06C) AS [Среднее 6], Avg(Кадры.К06Д) AS [Дисперсия 6], Avg(Кадры.К09) AS [Канал 9], Avg(Кадры.К16) AS [Канал 16], Avg(Кадры.К46) AS [Канал 6], Avg(Кадры.К66) AS [Канал 66], Avg(Кадры.К76) AS [Канал 76] FROM Сессии INNER JOIN Кадры ON Сессии.Номер = Кадры.Сессия";
        string avgQueryTail = " GROUP BY 1=1";

        // Конструктор также заполняет форму фильтр
        public MainWindow()
        {
            InitializeComponent();
            ShowQuery("");

            OdbcCommand query;
            OdbcDataReader read;
            List<string> opers = new List<string>();
            dataBase.Open();

            query = new OdbcCommand("SELECT DISTINCT Оператор FROM Сессии",
                dataBase);
            read = query.ExecuteReader();
            while (read.Read())
                opers.Add(read.GetString(0));


            query = new OdbcCommand("SELECT min(Дата), max(Дата) FROM Сессии",
                dataBase);
            read = query.ExecuteReader();
            if (read.Read())
                filter = new FilterWindow(opers.ToArray(),
                    read.GetDateTime(0), read.GetDateTime(1));
            else
                filter = new FilterWindow(opers.ToArray(),
                    DateTime.Now.AddYears(-1), DateTime.Now);

            dataBase.Close();
            foreach (DataGridViewColumn col in DataGrid.Columns)
                if (col.Index > 1)
                    filter.WhereGrid.Rows.Add(new string[] { col.HeaderText, "", "" });
        }

        // Обновление отображаемых данных
        void ShowQuery(string where)
        {
            OdbcDataAdapter adapter;
            DataSet data;

            if (where != "")
                where = " WHERE " + where;

            dataBase.Open();

            adapter = new OdbcDataAdapter(dataQuery + where, dataBase);
            adapter.Fill(data = new DataSet());
            DataGrid.DataSource = data;
            DataGrid.DataMember = data.Tables[0].ToString();
            DataGrid.Columns[0].Visible = false;

            adapter = new OdbcDataAdapter(avgQuery + where + avgQueryTail, dataBase);
            adapter.Fill(data = new DataSet());
            AvgGrid.DataSource = data;
            AvgGrid.DataMember = data.Tables[0].ToString();
            AvgGrid.Columns[0].Visible = false;

            dataBase.Close();
        }

        // Синхронная прокрутка гридов
        private void DataGrid_Scroll(object sender, ScrollEventArgs e)
        {
            AvgGrid.HorizontalScrollingOffset = DataGrid.HorizontalScrollingOffset;
        }
        private void AvgGrid_Scroll(object sender, ScrollEventArgs e)
        {
            DataGrid.HorizontalScrollingOffset = AvgGrid.HorizontalScrollingOffset;
        }

        // Использование фильтра
        private void MenuFilter_Click(object sender, EventArgs e)
        {
            filter.ShowDialog();
            ShowQuery(filter.Where());
        }

        // Предварительный просмотр на печать
        private void MenuPrint_Click(object sender, EventArgs e)
        {
            PrintDocument doc = new PrintDocument();
            doc.PrintPage += new PrintPageEventHandler(MenuPrint_Handler);
            doc.DefaultPageSettings.Landscape = true;
            PageIterator = PrintIterator = 0;

            PrintDialog dlg = new PrintDialog();
            dlg.Document = doc;
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                PrintPreviewDialog prtr = new PrintPreviewDialog();
                prtr.Document = doc;
                prtr.WindowState = FormWindowState.Maximized;
                prtr.ShowDialog();
            }
        }

        

        // Метод отрисовки печатной страницы
        private void MenuPrint_Handler(object sender, PrintPageEventArgs e)
        {
            float rowIterator = 20;
            if (PrintIterator == 0)
            {
                DrawString(e, "Отчёт от " +
                    DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss"), 100, 20, 2);
                DrawString(e, filter.Report(), 30, 50, 0);

                DrawString(e, "Средние значения:", 100, 95, 2);
                for (int i = 1; i < AvgGrid.Columns.Count; ++i)
                {
                    DrawString(e, AvgGrid.Columns[i].HeaderText,
                        i * 85 - 55, 115, 0);
                    string val = AvgGrid.Rows[0].Cells[i].Value.ToString();
                    DrawString(e, (val.Length > 8) ? val.Substring(0, 8) : val,
                        i * 85 - 55, 135, 0);
                }

                DrawString(e, "Все отобраные значения:", 100, 165, 2);
                rowIterator = 185;
            }

            for (int i = 1; i < AvgGrid.Columns.Count; ++i)
                DrawString(e, AvgGrid.Columns[i].HeaderText,
                    i * 85 - 55, rowIterator, 0);
            rowIterator += 20;

            while ((PrintIterator < DataGrid.Rows.Count) && (rowIterator < 770))
            {
                for (int i = 1; i < DataGrid.Columns.Count; ++i)
                    DrawString(e, (DataGrid.Rows[PrintIterator].
                        Cells[i].Value.ToString().Split(' '))[0],
                        i * 85 - 55, rowIterator, 0);
                rowIterator += 15;
                PrintIterator++;
            }

            DrawString(e, "Страница " + (++PageIterator).ToString(), 1080, 780, 0);
            e.HasMorePages = PrintIterator < DataGrid.Rows.Count;
        }

        // Ресурсы метода отрисовки
        int PrintIterator, PageIterator;
        private void DrawString(PrintPageEventArgs e, string text,
            float x, float y, float incF)
        {
            e.Graphics.DrawString(text, new Font("Arial", incF + 8),
                new SolidBrush(Color.Black), x, y);
        }


        // Экспорт в файл
        private void MenuExport_Click(object sender, EventArgs e)
        {
            SaveFileDialog file = new SaveFileDialog();
            file.DefaultExt = ".dat";
            file.AddExtension = true;
            file.FileName = Application.StartupPath + "\\Export_" + 
                DateTime.Now.ToString("yyyy-MM-dd_hh-mm-ss") + ".dat";
            file.ShowDialog();
            if (file.FileName == "")
                return;

            StreamWriter stream = new StreamWriter(file.FileName);
            foreach (DataGridViewRow row in DataGrid.Rows)
            {
                foreach (DataGridViewCell cell in row.Cells)
                    if (cell.ColumnIndex > 2)
                        stream.Write(cell.Value.ToString().Replace(',', '.') + "\t");
                stream.WriteLine();
            }
            stream.Close();
        }
    }
}
