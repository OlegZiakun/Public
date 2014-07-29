[ENG]

You must write on a pure C++ a class that able to quickly read the text log files of enormous size (tens and hundreds of megabytes) and issue the lines that satisfy of simplest regexp conditions: (a minimum of operators * and ?, a wider range of features is welcome):

symbol '*' - a sequence of any characters of unlimited length;
symbol "?" - any single character;
must correctly handled masks: *Some*, *Some, Some*, *****Some*** - there are no restrictions regarding the position of * in the mask.

The class will not expand and will not be a base class. The only problem: scanning and text search ANSI (not unicode) strings in files.

The class should have the following public interface:

class CLogReader
  {
public:
           CLogReader(...);
          ~CLogReader(...);

   bool    Open(...);                       // opening a file, false - error
   void    Close();                         // closing the file


   bool    SetFilter(const char *filter);   // settings of lines filter, false - error
   bool    GetNextLine(char *buf,           // request the next line found, 
                       const int bufsize);  // buf - buffer, bufsize - max length
                                            // false - the end of the file or error
  };


The implementation requirements:


Platform: Windows XP and higher
Functionality: maximum performance (caching search results and the file is not required);

Resources: Memory costs should be minimal (within reason);

Components: forbidden to use third-party libraries (including STL) and components. Allowed to use only WinAPI and CRT;
Exceptions: You can not use Windows and C++ exceptions;
The code must be absolutely "not killed" and protected from errors.

Formal requirements:

The code should be as simple as possible; 
The code should be as clean, beautiful and clear; The result should be ready class (cpp + h files) and console example (open the text file in a couple of megabytes and make the sample "order * closed") to use it. File and line selection should be specified in the arguments of example;

[RUS]

Необходимо написать на чистом С++ класс, умеющий максимально быстро читать текстовые лог-файлы огромных размеров (десятки и сотни мегабайт) и выдавать строки, удовлетворяющие условиям простейшего regexp: (как минимум операторы * и ?, более широкий набор возможностей приветствуется):

cимвол '*' - последовательность любых символов неограниченной длины;
cимвол "?" - один любой символ;
должны корректно отрабатываться маски: *Some*, *Some, Some*, *****Some*** - нет никаких ограничений на положение * в маске.

Класс не будет расширяться и не будет базовым классом. Единственная задача: сканирование и поиск текстовых ANSI (не unicode) строк в файлах. 


Класс должен иметь следующий публичный интерфейс:

class CLogReader
  {
public:
           CLogReader(...);
          ~CLogReader(...);

   bool    Open(...);                       // открытие файла, false - ошибка
   void    Close();                         // закрытие файла


   bool    SetFilter(const char *filter);   // установка фильтра строк, false - ошибка
   bool    GetNextLine(char *buf,           // запрос очередной найденной строки, 
                       const int bufsize);  // buf - буфер, bufsize - максимальная длина
                                            // false - конец файла или ошибка
  };

 

Требование к реализации:


Платформа: Windows XP и выше;
Функциональность: максимальная производительность (кэширование результатов поиска и файла не требуется);

Ресурсы: затраты памяти должны быть минимальны (в разумных пределах);

Компоненты: запрещено использование сторонних библиотек (в том числе STL) и компонентов. Разрешено использовать только WinAPI и CRT;
Исключения: нельзя использовать Windows и С++ исключения;
Код должен быть абсолютно «неубиваемый» и защищённым от ошибок.

Требования к оформлению:

Код должен быть максимально простым;
Код должен быть максимально чистым, красивым и понятным;
Результатом должен быть готовый класс (cpp + h файлы) и консольный пример (открыть текстовый файл в пару мегабайт и сделать выборку "order*closed") его использования. Файл и строка выбора должна указываться в аргументах примера;


