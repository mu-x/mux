using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Text.RegularExpressions;

namespace CodeToOne
{
    /// <summary> Обработчик кода </summary>
    class CodeBox
    {
        /// <summary> Имена файлов </summary>
        List<string> names = new List<string>();

        /// <summary> Коды файлов </summary>
        List<string> files = new List<string>();

        /// <summary> Загрузка файлов </summary>
        public void Read(string exts, string path)
        {
            preNames(exts, path);
            preFiles();
        }

        /// <summary> Редактирование кода </summary>
        public void Edit(bool ptab, bool tab, bool num, bool thiz, bool sys, bool php)
        {
            if (ptab) // Префикс Tab на 2 Sp
                for (int i = 10; i > 0; --i) for (int j = 0; j < files.Count; ++j)
                    files[j] = files[j].Replace("\r\n" + new string('\t', i),
                        "\r\n" + new string(' ', 2 * i));

            if (tab) // Все Tab на 2 Sp
                for (int j = 0; j < files.Count; ++j)
                        files[j] = files[j].Replace('\t', ' ');

            if (thiz) // Снятие this*
                for (int j = 0; j < files.Count; ++j)
                    files[j] = files[j].Replace("this->", "").Replace("this.", "");

            if (sys) // Снятие System*
                for (int j = 0; j < files.Count; ++j)
                {
                    files[j] = files[j].Replace("namespace System", "#####!")
                        .Replace("using System", "?????!");
                    files[j] = files[j].Replace("System::", "").Replace("System.", "");
                    files[j] = files[j].Replace("#####!", "namespace System")
                        .Replace("?????!", "using System");
                }

            if (num) // Номера строк
                for (int j = 0; j < files.Count; ++j)
                {
                    string[] lines = files[j].Split('\n');
                    for (int i = 0; i < lines.Length; ++i)
                        lines[i] = string.Format("{0:000}", i + 1)
                            + " " + lines[i];
                    files[j] = string.Join("\n", lines);
                }

            if (php) // Короткие тэги PHP
                for (int j = 0; j < files.Count; ++j)
                    files[j] = files[j].Replace("<?php", "<?").
                        Replace("<?echo", "<?=").Replace("<? echo", "<?=");
        }

        /// <summary> Запись в файл </summary>
        public void Write(string file)
        {
            StreamWriter text = new StreamWriter(file);

            foreach (string one in files)
                text.WriteLine(one + "\n\r");

            text.Close();
        }

        /// <summary> Подготовка имён </summary>
        void preNames(string exts, string path)
        {
            string[] tmpNames = Directory.GetFiles(path);
            string[] tmpExts = exts.Split(',');

            for (int i = 0; i < tmpExts.Length; ++i)
                tmpExts[i] = tmpExts[i].Trim();

            Regex reg = new Regex(".+(\\." + String.Join("|", tmpExts) + ")");
            names.Clear();

            foreach (string name in tmpNames)
                if (reg.Matches(name).Count > 0)
                    names.Add(name);
        }

        /// <summary> Подгоовка файлов </summary>
        void preFiles()
        {
            StreamReader text;
            files.Clear();

            foreach (string name in names)
            {
                text = new StreamReader(name, Encoding.GetEncoding(1251));
                files.Add(text.ReadToEnd());
                text.Close();
            }
        }
    }
}
