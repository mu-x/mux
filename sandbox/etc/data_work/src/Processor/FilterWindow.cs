using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Processor
{
    public partial class FilterWindow : Form
    {
        // Временные края базы
        private DateTime baseLow, baseHig;
        private string[] canals = { "К01", "К02", "К03", "К04", "К05", "К06С", "К06Д", "К09", "К16", "К46", "К66", "К76" };

        // Конструктор с дефолтами
        public FilterWindow(string[] oper, DateTime low, DateTime hig)
        {
            InitializeComponent();
            baseLow = low;
            baseHig = hig;
            OperBox.Items.AddRange(oper);
            NullBtn_Click(this, null);
        }

        // Создание условия запросов
        public string Where()
        {
            string where = "Сессии.Дата >= #" +
                DateLowBox.Value.ToString("MM.dd.yyyy").Replace(".", "/") +
                "# And Сессии.Дата <= #" +
                DateHigBox.Value.ToString("MM.dd.yyyy").Replace(".", "/") + "#";

            for (int i = 0; i < WhereGrid.Rows.Count; ++i)
            {
                if (WhereGrid.Rows[i].Cells[1].Value.ToString() != "")
                    where += " And Кадры.[" + canals[i] +
                        "] >= " + WhereGrid.Rows[i].Cells[1].Value;
                if (WhereGrid.Rows[i].Cells[2].Value.ToString() != "")
                    where += " And Кадры.[" + canals[i] +
                        "] <= " + WhereGrid.Rows[i].Cells[2].Value;
            }

            if (OperBox.SelectedIndex != 0)
                where += " And Сессии.Оператор = '" +
                    OperBox.SelectedItem.ToString() + "'";

            return where;
                
        }

        // Создание условия отчётов
        public string Report()
        {
            string text =
                "Оператор: \"" + OperBox.SelectedItem.ToString() + "\", " +
                "даты с " + DateLowBox.Value.ToString("dd.MM.yyyy") + " " +
                "по " + DateHigBox.Value.ToString("dd.MM.yyyy") + ", " +
                "ограничения: ";

            List<string> retr = new List<string>();
            for (int i = 0; i < WhereGrid.Rows.Count; ++i)
            {
                if (WhereGrid.Rows[i].Cells[1].Value.ToString() != "")
                    retr.Add(canals[i] + " >= " +
                        WhereGrid.Rows[i].Cells[1].Value);
                if (WhereGrid.Rows[i].Cells[2].Value.ToString() != "")
                    retr.Add(canals[i] + " >= " +
                        WhereGrid.Rows[i].Cells[2].Value);
            }

            string retrs = (retr.Count == 0) ? "отсутствуют" :
                String.Join(", ", retr.ToArray());
            return text + retrs + ".";
        }

        // Обнуление фильтров
        private void NullBtn_Click(object sender, EventArgs e)
        {
            OperBox.SelectedIndex = 0;
            DateLowBox.Value = baseLow;
            DateHigBox.Value = baseHig;

            foreach (DataGridViewRow row in WhereGrid.Rows)
            {
                row.Cells[1].Value = "";
                row.Cells[2].Value = "";
            }
        }

        // Элегантное закрытие формы
        private void OkBtn_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
