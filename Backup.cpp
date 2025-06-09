//C++ v. 17
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <windows.h>
#pragma warning(disable:4996)


std::string getCurrentDate() {
    std::time_t now = std::time(nullptr);
    std::tm now_tm = *std::localtime(&now);

    // Форматирование строки с текущей датой
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d_%H-%M-%S");
    return oss.str();
}

// Возвращаем расширение файла
std::string getFileExtension(const std::string& filename) {
    size_t dot_pos = filename.find_last_of(".");
    if (dot_pos != std::string::npos) {
        return filename.substr(dot_pos);
    }
    return "";                                                     // Если расширения нет, возвращаем пустую строку
}

bool copyFile(const std::string& sourcePath, const std::string& destinationDir, const std::string& FileName) {
    std::ifstream source(sourcePath, std::ios::binary);

    std::string Name = getCurrentDate();  //Запись времени

    std::string fileName = sourcePath.substr(sourcePath.find_last_of("/\\") + 1);
    std::string fileExtension = getFileExtension(fileName);                                       //Возвращаем значение расширения файла

    std::string newFileName = destinationDir + "/" + "/" + Name + "/" + FileName + fileExtension; //Записываем путь куда копировать файл   

    //Проверка с вызовом функции создания лога
    if (!source)
    {
        std::ofstream out("E:/log.txt", std::ios::app);
        if (out.is_open())
        {
            out << getCurrentDate() + " Error dont open file read " << std::endl;
        }
        out.close();
        return false;
    }


    std::filesystem::create_directory(destinationDir + "/" + Name);                 // Создание папки с уникальным именем в указанном каталоге


    //Проверка с вызовом функции создания лога
    std::ofstream destination(newFileName, std::ios::binary);
    if (!destination)
    {
        std::ofstream out("E:/log.txt", std::ios::app);
        if (out.is_open())
        {
            out << getCurrentDate() + " Error dont open file " << std::endl;
        }
        out.close();
        return false;
    }
    destination << source.rdbuf();     // Копируем содержимое
    return true;                       // Успешное копирование
}


int main()
{
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    int day_old = 0;
    std::string sourceFile;
    std::string destinationDirectory;
    std::string FileName;

    for (bool i = false; i == false; )
    {
        std::time_t now = std::time(0);
        std::tm* ltm = std::localtime(&now);
        int day_new = ltm->tm_mday;                 //запись текущего числа tm_mday

        std::time_t now3 = std::time(0);
        std::tm* ltm3 = std::localtime(&now3);
        int hour = ltm3->tm_hour;                   //запись текущего времени, часы

        if (day_new != day_old && hour == 10)                     //&& hour == 10                                   //Проверка временного интервала 
        {
            sourceFile = "D:/Data/ALARMLOG.001";                                                     //Путь к исходному файлу к базе данных Алармов
            destinationDirectory = "E:/ALARM";                                                  //Папка назначения
            FileName = "ALARMLOG";

            if (copyFile(sourceFile, destinationDirectory, FileName))
            {
                std::ofstream out("E:/log.txt", std::ios::app);
                if (out.is_open())
                {
                    out << getCurrentDate() + " Copy file 'ALARMLOG.001' complete " << std::endl;
                }
                out.close();
            }
            else
            {
                std::ofstream out("E:/log.txt", std::ios::app);
                if (out.is_open())
                {
                    out << getCurrentDate() + " Eror copy file 'ALARMLOG.001' " << std::endl;
                }
                out.close();
            }

            sourceFile = "C:/ProgramData/MySQL/MySQL Server 8.0/Data/atlaspulkovodb/naliv.ibd"; //Путь к исходному файлу к базе Налива
            destinationDirectory = "E:/NALIV";                                                  //Папка назначения
            FileName = "naliv";

            if (copyFile(sourceFile, destinationDirectory, FileName))
            {
                std::ofstream out("E:/log.txt", std::ios::app);
                if (out.is_open())
                {
                    out << getCurrentDate() + " Copy file 'naliv.ibd' complete " << std::endl;
                }
                out.close();
            }
            else
            {
                std::ofstream out("E:/log.txt", std::ios::app);
                if (out.is_open())
                {
                    out << getCurrentDate() + " Eror copy file 'naliv.ibd' " << std::endl;
                }
                out.close();
            }

            sourceFile = "C:/ProgramData/MySQL/MySQL Server 8.0/Data/atlaspulkovodb/sliv.ibd"; //Путь к исходному файлу к базе Слива
            destinationDirectory = "E:/SLIV";                                                  //Папка назначения
            FileName = "sliv";

            if (copyFile(sourceFile, destinationDirectory, FileName))
            {
                std::ofstream out("E:/log.txt", std::ios::app);
                if (out.is_open())
                {
                    out << getCurrentDate() + " Copy file 'sliv.ibd' complete " << std::endl;
                }
                out.close();
            }
            else
            {
                std::ofstream out("E:/log.txt", std::ios::app);
                if (out.is_open())
                {
                    out << getCurrentDate() + " Eror copy file 'sliv.ibd' " << std::endl;
                }
                out.close();
            }

            day_old = day_new;
        }
    }
}
