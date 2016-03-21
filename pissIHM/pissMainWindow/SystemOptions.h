#ifndef SYSTEMOPTIONS_H
#define SYSTEMOPTIONS_H

#include <QFrame>
#include <QGridLayout>
#include <QComboBox>
#include <QColor>
#include <QPushButton>
#include <QLabel>


class SystemOptions : public QFrame
{
    Q_OBJECT

private:
    QGridLayout *systemOptionsLayout;

    QComboBox *systemBackgroundColorOptions;
    QComboBox *systemWorkSpaceColor;

    QLabel *systemBackgroundColorOptionsLabel;

    QPushButton *confirmButton;
    QPushButton * cancelButton;

    QString comboBoxStyle;

    QString systemGlobalBackgroundColor;

public:
    void initVariable();
    void constructIHM();
    void setConnections();
    void fillColorList(QComboBox *systemBackgroundColorOptions);
    QString getSystemGlobalBackgroundColor();

signals:
    void confirm();
    void cancel();

public slots:
    void onConfirmButtonClicked();
    void onCancelButtonClicked();
    void systemColorOptionChanged();

public:
    SystemOptions();
};

#endif // SYSTEMOPTIONS_H
