#ifndef BASEPUMPSCREEN_H
#define BASEPUMPSCREEN_H

#include <QBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QLineEdit>

#define REGISTER_DERIVED_TYPE(TYPE) \
namespace { \
    struct TYPE##Registrar { \
        TYPE##Registrar() { \
            BasePumpScreen::registerType(#TYPE, []() -> BasePumpScreen* {return new TYPE();}); \
    } \
}; \
    static TYPE##Registrar global_##TYPE##Registrar; \
}

class BasePumpScreen : public QWidget {
        Q_OBJECT

    public:
        BasePumpScreen(QWidget* parent = nullptr, const QString& title = "",
                       bool = true, bool = false, bool = false);
        BasePumpScreen(bool pop = true);

        bool isPopup();
        void setTitle(const QString& title);

        using CreatorFunc = std::function<BasePumpScreen*()>;
        static QList<BasePumpScreen*> createAllDerived();
        static void registerType(const QString& name, CreatorFunc func);

    signals:
        void backClicked();
        void addClicked();
        void confirmed();

    protected:
        QWidget* buttonBar;
        QLineEdit* titleEdit;
        bool popup;

        void renameTitle();

    private slots:
        void completeTitleRename();

    private:
        void initialBarSetup();
        void addButton(QPushButton*, const QString&, void (BasePumpScreen::*signal)());
        static QMap<QString, CreatorFunc>& registry();
};

#endif // BASEPUMPSCREEN_H
