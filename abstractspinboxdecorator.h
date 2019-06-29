#ifndef ABSTRACTSPINBOXDECORATOR_H
#define ABSTRACTSPINBOXDECORATOR_H

#include <QLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QTimeEdit>
#include <QWidget>

class AbstractSpinBoxDecorator : public QWidget {
  Q_OBJECT

  static const auto buttonsWidth = 19;
  static const auto buttonsHeight = buttonsWidth / 2;
  static inline const QString fontResourcePath = "FontAwesome";

  QVBoxLayout *buttonsLayout;
  QWidget *buttonsWidget;
  QAbstractSpinBox *_abstractSpinBox;
  QPushButton *upButton;
  QPushButton *downButton;
  int fontPixelSize = QFont().pixelSize();

  void setup();
  void applyStyleSheet();

  void createLayout();
  void createButtonsLayout();
  void createButtonsWidget();
  void createButtons();

  void addSpinboxToLayout();

  QPushButton *makeButton(QString text = "");

protected:
  virtual void connectImplementation() = 0;
  QAbstractSpinBox *abstractSpinBox() const;

public:
  explicit AbstractSpinBoxDecorator(QAbstractSpinBox *_abstractSpinBox,
                                    QWidget *parent = nullptr);
  virtual ~AbstractSpinBoxDecorator() {}

  int getFontPixelSize() const;
  void setFontPixelSize(int value);

public slots:
  void stepUp();
  void stepDown();
};

class SpinBoxDecorator : public AbstractSpinBoxDecorator {
  Q_OBJECT
  void connectImplementation() {
    connect(spinBox(), QOverload<int>::of(&QSpinBox::valueChanged), this,
            &SpinBoxDecorator::valueChanged);
  }

public:
  using AbstractSpinBoxDecorator::AbstractSpinBoxDecorator;

  QSpinBox *spinBox() { return static_cast<QSpinBox *>(abstractSpinBox()); }

public slots:
  void valueChanged(int value) { spinBox()->setValue(value); }
};

class TimeEditDecorator : public AbstractSpinBoxDecorator {
  Q_OBJECT
  void connectImplementation() {
    connect(timeEdit(), &QTimeEdit::timeChanged, this,
            &TimeEditDecorator::timeChanged);
  }

public:
  using AbstractSpinBoxDecorator::AbstractSpinBoxDecorator;

  QTimeEdit *timeEdit() { return static_cast<QTimeEdit *>(abstractSpinBox()); }

public slots:
  void timeChanged(QTime time) { timeEdit()->setTime(time); }
};

#endif // ABSTRACTSPINBOXDECORATOR_H