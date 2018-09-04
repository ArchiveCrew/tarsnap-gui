#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QCoreApplication>
#include <QMap>
#include <QString>
#include <QTranslator>

#define LANG_AUTO "Auto"

class Translator
{
public:
    static Translator &instance();
    void translateApp(QCoreApplication *app, QString lang);
    QStringList languageList();

private:
    Translator();
    Translator(Translator const &);
    Translator &operator=(Translator const &);

    QMap<QString, QString> _languageMap;
    QTranslator *_qtTranslator;
    QTranslator *_appTranslator;
};

#endif // TRANSLATOR_H
