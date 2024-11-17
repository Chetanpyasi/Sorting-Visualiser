#ifndef SORTINGVISUALIZER_H
#define SORTINGVISUALIZER_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QVector>
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QStringList>
#include <QSplitter>
#include <QPair>

class SortingVisualizer : public QMainWindow {
    Q_OBJECT

public:
    SortingVisualizer(QWidget *parent = nullptr);

private slots:
    void visualizeAlgorithm(const QString &algorithm, const QString &input);
    void updateVisualization();
    void play();
    void pause();
    void resetVisualization();

private:
    void bubbleSort();
    void insertionSort();
    void selectionSort();
    void mergeSort(int left, int right);
    void quickSort(int left, int right);
    void heapSort();
    void countingSort();
    void radixSort();
    void shellSort();
    void bucketSort();

    void validateInput(QLineEdit *inputField);
    void showErrorMessage(const QString &message);

    QVector<int> getInputArray(const QString &input);
    void merge(int left, int mid, int right);
    int partition(int left, int right);
    void heapify(QVector<int>& array, int n, int root);
    void countingSortForRadix(int exp);
    void drawArray(const QVector<int> &array, int highlightIndex1 = -1, int highlightIndex2 = -1);
    bool isBarVisualization = false;

    QVector<int> array;
    void addComparisonBox();
    bool compbox = true ;
    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
    QVector<QVector<int>> steps;
    int currentStep = 0;
    QTimer *timer;
    bool isPlaying = false;
    QVector<QPair<int, int>> highlights; // Store the highlights for playback
    QPushButton* currentButton = nullptr; // Track the currently active button
    QWidget *overlayWidget;
    bool showValues;

};

#endif // SORTINGVISUALIZER_H
