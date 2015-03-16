using System;
using System.Collections.Generic;
using System.Text;

namespace OpenXmlEdit
{
    static class Messages
    {
        public class MessagesStruct
        {
            public string T, N, Q, E;
            
            public MessagesStruct(string[] arr)
            {
                T = arr[0]; N = arr[1];
                Q = arr[2]; E = arr[3];
            }
        }

        public static MessagesStruct File = new MessagesStruct(new string[]
        {
            "Создание файла...",
            "Введите име корневого злемента:",
            "Сохранить текущий файл?",
            "Ошибка кода XML"
        });

        public static MessagesStruct Node = new MessagesStruct(new string[]
        {
            "Создание узла...",
            "Введите име узла:",
            "Удалить узел X?",
            "Невозможно создать узел"
        });

        public static MessagesStruct Prop = new MessagesStruct(new string[]
        {
            "Создание атрибута...",
            "Введите име атрибута:",
            "Удалить атрибут X узла Y?",
            "Невозможно создать атрибут"
        });
    }
}
