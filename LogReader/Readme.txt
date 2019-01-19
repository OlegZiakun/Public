[ENG]

This is implement pure C++ a class that able to quickly read the text log files of enormous size (tens and hundreds of megabytes) and issue the lines that satisfy of simplest regexp conditions: (a minimum of operators * and ?, a wider range of features is welcome):

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

Íåîáõîäèìî íàïèñàòü íà ÷èñòîì Ñ++ êëàññ, óìåþùèé ìàêñèìàëüíî áûñòðî ÷èòàòü òåêñòîâûå ëîã-ôàéëû îãðîìíûõ ðàçìåðîâ (äåñÿòêè è ñîòíè ìåãàáàéò) è âûäàâàòü ñòðîêè, óäîâëåòâîðÿþùèå óñëîâèÿì ïðîñòåéøåãî regexp: (êàê ìèíèìóì îïåðàòîðû * è ?, áîëåå øèðîêèé íàáîð âîçìîæíîñòåé ïðèâåòñòâóåòñÿ):

cèìâîë '*' - ïîñëåäîâàòåëüíîñòü ëþáûõ ñèìâîëîâ íåîãðàíè÷åííîé äëèíû;
cèìâîë "?" - îäèí ëþáîé ñèìâîë;
äîëæíû êîððåêòíî îòðàáàòûâàòüñÿ ìàñêè: *Some*, *Some, Some*, *****Some*** - íåò íèêàêèõ îãðàíè÷åíèé íà ïîëîæåíèå * â ìàñêå.

Êëàññ íå áóäåò ðàñøèðÿòüñÿ è íå áóäåò áàçîâûì êëàññîì. Åäèíñòâåííàÿ çàäà÷à: ñêàíèðîâàíèå è ïîèñê òåêñòîâûõ ANSI (íå unicode) ñòðîê â ôàéëàõ. 


Êëàññ äîëæåí èìåòü ñëåäóþùèé ïóáëè÷íûé èíòåðôåéñ:

class CLogReader
  {
public:
           CLogReader(...);
          ~CLogReader(...);

   bool    Open(...);                       // îòêðûòèå ôàéëà, false - îøèáêà
   void    Close();                         // çàêðûòèå ôàéëà


   bool    SetFilter(const char *filter);   // óñòàíîâêà ôèëüòðà ñòðîê, false - îøèáêà
   bool    GetNextLine(char *buf,           // çàïðîñ î÷åðåäíîé íàéäåííîé ñòðîêè, 
                       const int bufsize);  // buf - áóôåð, bufsize - ìàêñèìàëüíàÿ äëèíà
                                            // false - êîíåö ôàéëà èëè îøèáêà
  };

 

Òðåáîâàíèå ê ðåàëèçàöèè:


Ïëàòôîðìà: Windows XP è âûøå;
Ôóíêöèîíàëüíîñòü: ìàêñèìàëüíàÿ ïðîèçâîäèòåëüíîñòü (êýøèðîâàíèå ðåçóëüòàòîâ ïîèñêà è ôàéëà íå òðåáóåòñÿ);

Ðåñóðñû: çàòðàòû ïàìÿòè äîëæíû áûòü ìèíèìàëüíû (â ðàçóìíûõ ïðåäåëàõ);

Êîìïîíåíòû: çàïðåùåíî èñïîëüçîâàíèå ñòîðîííèõ áèáëèîòåê (â òîì ÷èñëå STL) è êîìïîíåíòîâ. Ðàçðåøåíî èñïîëüçîâàòü òîëüêî WinAPI è CRT;
Èñêëþ÷åíèÿ: íåëüçÿ èñïîëüçîâàòü Windows è Ñ++ èñêëþ÷åíèÿ;
Êîä äîëæåí áûòü àáñîëþòíî «íåóáèâàåìûé» è çàùèù¸ííûì îò îøèáîê.

Òðåáîâàíèÿ ê îôîðìëåíèþ:

Êîä äîëæåí áûòü ìàêñèìàëüíî ïðîñòûì;
Êîä äîëæåí áûòü ìàêñèìàëüíî ÷èñòûì, êðàñèâûì è ïîíÿòíûì;
Ðåçóëüòàòîì äîëæåí áûòü ãîòîâûé êëàññ (cpp + h ôàéëû) è êîíñîëüíûé ïðèìåð (îòêðûòü òåêñòîâûé ôàéë â ïàðó ìåãàáàéò è ñäåëàòü âûáîðêó "order*closed") åãî èñïîëüçîâàíèÿ. Ôàéë è ñòðîêà âûáîðà äîëæíà óêàçûâàòüñÿ â àðãóìåíòàõ ïðèìåðà;


