#include "SortingVisualizer.h"
#include <QCoreApplication>
#include <QHBoxLayout>
#include <QBrush>
#include <QColor>
#include <QPen>
#include "SortingVisualizer.h"
#include <QCoreApplication>
#include <QHBoxLayout>
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>




SortingVisualizer::SortingVisualizer(QWidget *parent) : QMainWindow(parent), timer(new QTimer(this)) {
    QWidget *centralWidget = new QWidget(this);
    QSplitter *splitter = new QSplitter(Qt::Vertical, centralWidget);

    // Visualization (graphics view) fixed height
    graphicsView = new QGraphicsView(this);
    graphicsView->setFixedHeight(300); // Set fixed height to avoid resizing
    graphicsView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); // Expand width, fixed height
    splitter->addWidget(graphicsView);

    // Create an overlay widget for the comparison box
    overlayWidget = new QWidget(graphicsView);
    overlayWidget->setFixedHeight(50); // Small height for comparison box area
    overlayWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    overlayWidget->setStyleSheet("background-color: rgba(255, 255, 255, 0.8);"); // Semi-transparent background
    overlayWidget->move(0, 0); // Position the overlay at the top of the graphics view
    overlayWidget->raise(); // Make sure the overlay stays on top

    QHBoxLayout *overlayLayout = new QHBoxLayout(overlayWidget);
    overlayLayout->setContentsMargins(0, 0, 0, 0);
    overlayLayout->setSpacing(10);
    overlayWidget->setLayout(overlayLayout);

    // Add comparison boxes
    addComparisonBox();

    // Rest of the controls for sorting algorithms and user input
    QWidget *controlsWidget = new QWidget(this);
    QVBoxLayout *controlsLayout = new QVBoxLayout(controlsWidget);

    QLabel *inputLabel = new QLabel("Enter array elements (comma separated):");
    QLineEdit *inputField = new QLineEdit(this);
    controlsLayout->addWidget(inputLabel);
    controlsLayout->addWidget(inputField);

    // Add button for file upload
    QPushButton *uploadFileButton = new QPushButton("Choose File", this);
    connect(uploadFileButton, &QPushButton::clicked, this, [this, inputField]() {
        QString fileName = QFileDialog::getOpenFileName(this, "Open Text File", "", "Text Files (*.txt)");
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                QString fileContent = in.readAll().trimmed();
                inputField->setText(fileContent); // Display file content in the input field
                file.close();
            }
        }
    });
    controlsLayout->addWidget(uploadFileButton);

    QStringList algorithms = {"Bubble Sort", "Insertion Sort", "Selection Sort",
                              "Merge Sort", "Quick Sort", "Heap Sort",
                              "Counting Sort", "Radix Sort", "Shell Sort",
                              "Bucket Sort"};

    for (const QString &algo : algorithms) {
        QPushButton *button = new QPushButton(algo, this);
        connect(button, &QPushButton::clicked, this, [this, button, algo, inputField]() {
            if (inputField->text().trimmed().isEmpty()) {
                QLabel *errorLabel = new QLabel("Please enter an input first!", this);
                errorLabel->setStyleSheet("color: red");
                errorLabel->setAlignment(Qt::AlignCenter);
                errorLabel->setWordWrap(true);
                QLayout *layout = this->centralWidget()->layout();
                for (int i = layout->count() - 1; i >= 0; --i) {
                    QLayoutItem* item = layout->itemAt(i);
                    if (QLabel* label = qobject_cast<QLabel*>(item->widget())) {
                        if (label->text() == "Invalid input! Please enter numeric values only." ||
                            label->text() == "Please enter an input first!") {
                            layout->removeItem(item);
                            delete item->widget();
                            delete item;
                        }
                    }
                }
                layout->addWidget(errorLabel);
                return;
            }

            if (currentButton) {
                currentButton->setStyleSheet(""); // Reset previous button to default color
            }

            button->setStyleSheet("background-color: green"); // Change current button color to green
            currentButton = button; // Update currentButton to the newly clicked button

            visualizeAlgorithm(algo, inputField->text());
        });

        controlsLayout->addWidget(button);
    }

    QPushButton *resetButton = new QPushButton("Reset", this);
    connect(resetButton, &QPushButton::clicked, this, &SortingVisualizer::resetVisualization);
    controlsLayout->addWidget(resetButton);

    QPushButton *quitButton = new QPushButton("Quit", this);
    connect(quitButton, &QPushButton::clicked, this, &QWidget::close);
    controlsLayout->addWidget(quitButton);

    QPushButton *playButton = new QPushButton("Play", this);
    QPushButton *pauseButton = new QPushButton("Pause", this);
    connect(playButton, &QPushButton::clicked, this, &SortingVisualizer::play);
    connect(pauseButton, &QPushButton::clicked, this, &SortingVisualizer::pause);
    controlsLayout->addWidget(playButton);
    controlsLayout->addWidget(pauseButton);

    controlsWidget->setLayout(controlsLayout);
    splitter->addWidget(controlsWidget);
    setCentralWidget(splitter);
    setWindowTitle("Sorting Algorithm Visualizer");

    connect(timer, &QTimer::timeout, this, &SortingVisualizer::updateVisualization);
}

void SortingVisualizer::showErrorMessage(const QString &message) {
    QLabel *errorLabel = new QLabel(message, this);
    errorLabel->setStyleSheet("color: red");
    errorLabel->setAlignment(Qt::AlignCenter);
    errorLabel->setWordWrap(true);

    QLayout *layout = this->centralWidget()->layout();
    // Remove any existing error messages
    for (int i = layout->count() - 1; i >= 0; --i) {
        QLayoutItem* item = layout->itemAt(i);
        if (QLabel* label = qobject_cast<QLabel*>(item->widget())) {
            layout->removeItem(item);
            delete item->widget();
            delete item;
        }
    }
    layout->addWidget(errorLabel);
}

void SortingVisualizer::validateInput(QLineEdit *inputField) {
    if (inputField->text().trimmed().isEmpty()) {
        showErrorMessage("Please enter an input first!");
        return;
    }

    // Add other validation steps here
}

void SortingVisualizer::addComparisonBox() {
    // Get the current layout of the overlay widget
    QHBoxLayout *layout = qobject_cast<QHBoxLayout *>(overlayWidget->layout());

    // Create the red comparison box and label
    QFrame *redBoxFrame = new QFrame();
    redBoxFrame->setStyleSheet("background-color: red; border: 1px solid black;");
    redBoxFrame->setFixedSize(20, 20);
    QLabel *redLabel = new QLabel("Red: Being compared");

    QFrame *blueBoxFrame = new QFrame();
    blueBoxFrame->setStyleSheet("background-color: blue; border: 1px solid black;");
    blueBoxFrame->setFixedSize(20, 20);
    QLabel *blueLabel = new QLabel("Blue: unsorted");

    QFrame *yellowBoxFrame = new QFrame();
    yellowBoxFrame->setStyleSheet("background-color: yellow; border: 1px solid black;");
    yellowBoxFrame->setFixedSize(20, 20);
    QLabel *yellowLabel = new QLabel("Yellow: sorted array");

    // Create the green comparison box and label
    QFrame *greenBoxFrame = new QFrame();
    greenBoxFrame->setStyleSheet("background-color: green; border: 1px solid black;");
    greenBoxFrame->setFixedSize(20, 20);
    QLabel *greenLabel = new QLabel("Green: Being compared");

    // Add the boxes and labels to the layout
    layout->addWidget(redBoxFrame);
    layout->addWidget(redLabel);
    layout->addWidget(greenBoxFrame);
    layout->addWidget(greenLabel);
    layout->addWidget(blueBoxFrame);
    layout->addWidget(blueLabel);
    layout->addWidget(yellowBoxFrame);
    layout->addWidget(yellowLabel);
}


QVector<int> SortingVisualizer::getInputArray(const QString &input) {
    QStringList inputList = input.split(',', Qt::SkipEmptyParts);
    QVector<int> result;

    for (const QString &value : inputList) {
        bool ok;
        int num = value.trimmed().toInt(&ok);
        if (ok) {
            result.append(num);
        } else {
            return {}; // Return an empty vector if invalid input is found
        }
    }

    return result;
}

void SortingVisualizer::visualizeAlgorithm(const QString &algorithm, const QString &input) {
    array = getInputArray(input);

    if (array.isEmpty()) {
        QLabel *errorLabel = new QLabel("Invalid input! Please enter numeric values only.", this);
        errorLabel->setStyleSheet("color: red");
        errorLabel->setAlignment(Qt::AlignCenter);
        errorLabel->setWordWrap(true);
        centralWidget()->layout()->addWidget(errorLabel);
        return;
    }

    scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);

    // Determine if we need to switch to bars visualization
    isBarVisualization = array.size() > 4; // Use bars if the array has more than 15 elements
    graphicsView->setFixedHeight(isBarVisualization ? 300 : 400);  // Adjust height based on visualization type

    steps.clear();
    highlights.clear();
    currentStep = 0;

    if (algorithm == "Bubble Sort") {
        bubbleSort();
    } else if (algorithm == "Insertion Sort") {
        insertionSort();
    } else if (algorithm == "Selection Sort") {
        selectionSort();
    } else if (algorithm == "Merge Sort") {
        mergeSort(0, array.size() - 1);
    } else if (algorithm == "Quick Sort") {
        quickSort(0, array.size() - 1);
    } else if (algorithm == "Heap Sort") {
        heapSort();
    } else if (algorithm == "Counting Sort") {
        countingSort();
    } else if (algorithm == "Radix Sort") {
        radixSort();
    } else if (algorithm == "Shell Sort") {
        shellSort();
    } else if (algorithm == "Bucket Sort") {
        bucketSort();
    }
}

void SortingVisualizer::updateVisualization() {
    if (currentStep < steps.size()) {
        // Retrieve highlight indices for the current step
        int highlightIndex1 = (currentStep < highlights.size()) ? highlights[currentStep].first : -1;
        int highlightIndex2 = (currentStep < highlights.size()) ? highlights[currentStep].second : -1;

        drawArray(steps[currentStep], highlightIndex1, highlightIndex2); // Draw each step of the sorting
        if (compbox){
            addComparisonBox();
            compbox = false;
        }else{};
        currentStep++;
    } else {
        // When the sorting finishes, turn all bars of the sorted array yellow
        drawArray(steps.last(), -1, -1);  // steps.last() is the final sorted array
        timer->stop();  // Stop the timer after the final step
        pause();
    }
}


void SortingVisualizer::play() {
    if (!isPlaying) {
        isPlaying = true;
        timer->start(15); // Set timer interval to 1500 ms
    }
}

void SortingVisualizer::pause() {
    if (isPlaying) {
        isPlaying = false;
        timer->stop();
    }
}

void SortingVisualizer::resetVisualization() {
    array.clear();
    steps.clear();
    highlights.clear();
    currentStep = 0;
    scene->clear();
    timer->stop(); // Stop the timer on reset
    isPlaying = false; // Update playing status
}

void SortingVisualizer::drawArray(const QVector<int> &array, int highlightIndex1, int highlightIndex2) {
    scene->clear();

    int arraySize = array.size();
    int boxWidth = graphicsView->width() / arraySize;

    // Check whether to draw boxes or bars
    if (isBarVisualization) {
        int maxElement = *std::max_element(array.begin(), array.end());

        for (int i = 0; i < arraySize; ++i) {
            // If no elements are being highlighted, the sorting is complete, so color everything yellow
            QColor barColor = (highlightIndex1 == -1 && highlightIndex2 == -1) ? Qt::yellow :
                                  (i == highlightIndex1) ? Qt::red : (i == highlightIndex2) ? Qt::green : Qt::blue;

            int barHeight = 250 * array[i] / maxElement;  // Scale bar height relative to the largest element

            QGraphicsRectItem *rect = scene->addRect(i * boxWidth, 300 - barHeight, boxWidth - 1, barHeight, QPen(Qt::black), QBrush(barColor));

            QGraphicsTextItem *textItem = scene->addText(QString::number(array[i]));
            textItem->setPos(i * boxWidth + (boxWidth / 4), 300 - barHeight - 20);
            textItem->setDefaultTextColor(Qt::black);  // Set text color (optional)
        }

    } else {
        // Drawing boxes for small arrays
        for (int i = 0; i < arraySize; ++i) {
            QColor boxColor = (highlightIndex1 == -1 && highlightIndex2 == -1) ? Qt::yellow :
                                  (i == highlightIndex1) ? Qt::red : (i == highlightIndex2) ? Qt::green : Qt::blue;

            QGraphicsRectItem *rect = scene->addRect(i * boxWidth, 300 - 30, boxWidth - 1, 30, QPen(Qt::black), QBrush(boxColor));
            QGraphicsTextItem *textItem = scene->addText(QString::number(array[i]));
            textItem->setPos(i * boxWidth + boxWidth / 4, 270);
        }
    }

    graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

// Bubble Sort
void SortingVisualizer::bubbleSort() {
    QVector<int> tempArray = array;
    steps.push_back(tempArray); // Initial state

    for (int i = 0; i < tempArray.size() - 1; i++) {
        for (int j = 0; j < tempArray.size() - i - 1; j++) {
            if (tempArray[j] > tempArray[j + 1]) {
                std::swap(tempArray[j], tempArray[j + 1]);
                steps.push_back(tempArray); // Store each step
                highlights.append({j, j + 1}); // Highlight indices
            }
        }
    }
    steps.push_back(tempArray); // Final state
}
void SortingVisualizer::insertionSort() {
    QVector<int> tempArray = array;
    steps.push_back(tempArray); // Initial state

    for (int i = 1; i < tempArray.size(); i++) {
        int key = tempArray[i];
        int j = i - 1;

        // Highlight the key element to be inserted (using a pair with the same index)
        highlights.append(qMakePair(i, i)); // Highlight the key being moved
        steps.push_back(tempArray); // Store current step

        while (j >= 0 && tempArray[j] > key) {
            tempArray[j + 1] = tempArray[j]; // Shift larger elements to the right

            // Highlight the comparison and shifting
            highlights.append(qMakePair(j, j + 1)); // Highlight the indices being compared and shifted
            steps.push_back(tempArray); // Store current state of array
            j--;
        }

        // Insert the key element at its correct position
        tempArray[j + 1] = key;

        // Highlight the final insertion point (using a pair with the same index)
        highlights.append(qMakePair(j + 1, j + 1)); // Highlight the insertion index
        steps.push_back(tempArray); // Store the state after insertion
    }

    // Store the final sorted state
    steps.push_back(tempArray);
}

// Selection Sort
void SortingVisualizer::selectionSort() {
    QVector<int> tempArray = array;
    steps.push_back(tempArray); // Initial state

    for (int i = 0; i < tempArray.size() - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < tempArray.size(); j++) {
            if (tempArray[j] < tempArray[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(tempArray[i], tempArray[minIndex]);
        steps.push_back(tempArray); // Store each step
        highlights.append({i, minIndex}); // Highlight indices
    }
    steps.push_back(tempArray); // Final state
}

// Merge Sort
void SortingVisualizer::mergeSort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

void SortingVisualizer::merge(int left, int mid, int right) {
    // Create temporary arrays
    QVector<int> leftArray(array.begin() + left, array.begin() + mid + 1);
    QVector<int> rightArray(array.begin() + mid + 1, array.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < leftArray.size() && j < rightArray.size()) {
        if (leftArray[i] <= rightArray[j]) {
            array[k++] = leftArray[i++];
        } else {
            array[k++] = rightArray[j++];
        }
    }

    while (i < leftArray.size()) {
        array[k++] = leftArray[i++];
    }

    while (j < rightArray.size()) {
        array[k++] = rightArray[j++];
    }

    steps.push_back(array); // Store each step after merging
    highlights.append({left, right}); // Highlight indices
}

// Quick Sort
void SortingVisualizer::quickSort(int left, int right) {
    if (left < right) {
        int pivotIndex = partition(left, right);
        quickSort(left, pivotIndex - 1);
        quickSort(pivotIndex + 1, right);
    }
}

int SortingVisualizer::partition(int left, int right) {
    int pivot = array[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (array[j] < pivot) {
            i++;
            std::swap(array[i], array[j]);
            steps.push_back(array); // Store each step
            highlights.append({i, j}); // Highlight indices
        }
    }
    std::swap(array[i + 1], array[right]);
    steps.push_back(array); // Store each step
    highlights.append({i + 1, right}); // Highlight indices
    return i + 1;
}

// Heap Sort
void SortingVisualizer::heapSort() {
    QVector<int> tempArray = array;
    steps.push_back(tempArray); // Store initial state
    int n = tempArray.size();

    // Build heap (rearrange the array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(tempArray, n, i);  // Build heap from tempArray
    }

    // One by one extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        std::swap(tempArray[0], tempArray[i]);
        steps.push_back(tempArray); // Store each step after swapping
        highlights.append({0, i}); // Highlight the swapped elements
        heapify(tempArray, i, 0);  // Heapify the reduced heap
    }

    array = tempArray; // Update the original array with sorted values
    steps.push_back(array); // Store the final sorted state
}

void SortingVisualizer::heapify(QVector<int> &array, int n, int root) {
    int largest = root; // Initialize largest as root
    int left = 2 * root + 1; // left = 2*i + 1
    int right = 2 * root + 2; // right = 2*i + 2

    // Check if left child exists and is greater than root
    if (left < n && array[left] > array[largest]) {
        largest = left;
    }

    // Check if right child exists and is greater than largest so far
    if (right < n && array[right] > array[largest]) {
        largest = right;
    }

    // If largest is not root, swap it with root
    if (largest != root) {
        std::swap(array[root], array[largest]);
        steps.push_back(array); // Store the current state after swap
        highlights.append({root, largest}); // Highlight indices
        // Recursively heapify the affected sub-tree
        heapify(array, n, largest);
    }
}

// Counting Sort
void SortingVisualizer::countingSort() {
    if (array.isEmpty()) return;

    int maxValue = *std::max_element(array.begin(), array.end());
    QVector<int> count(maxValue + 1, 0);
    QVector<int> output(array.size());

    // Count occurrences
    for (int num : array) {
        count[num]++;
    }

    // Modify the count array
    for (int i = 1; i <= maxValue; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = array.size() - 1; i >= 0; i--) {
        output[count[array[i]] - 1] = array[i];
        count[array[i]]--;

        // Store the current state of the output array and highlight the current element
        steps.push_back(output); // Save the state of the output array
        highlights.append({count[array[i]], count[array[i]] + 1}); // Highlight current element and its position in the output array
    }

    // Update the original array with sorted values
    array = output;
    steps.push_back(array); // Store the final sorted state
}

// Radix Sort
void SortingVisualizer::radixSort() {
    int maxValue = *std::max_element(array.begin(), array.end());
    for (int exp = 1; maxValue / exp > 0; exp *= 10) {
        countingSortForRadix(exp);
    }
}

void SortingVisualizer::countingSortForRadix(int exp) {
    int n = array.size();
    QVector<int> output(n);
    QVector<int> count(10, 0);

    // Count occurrences based on the current digit
    for (int i = 0; i < n; i++) {
        count[(array[i] / exp) % 10]++;
    }

    // Modify the count array
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[(array[i] / exp) % 10] - 1] = array[i];
        count[(array[i] / exp) % 10]--;

        // Store the current state of the output array and highlight the current element
        steps.push_back(output); // Save the state of the output array after each insertion
        highlights.append({count[(array[i] / exp) % 10], count[(array[i] / exp) % 10] + 1}); // Highlight current element and its new position
    }

    // Update the original array with the sorted values
    array = output;
    steps.push_back(array); // Store the final state after processing this digit
}

// Shell Sort
void SortingVisualizer::shellSort() {
    QVector<int> tempArray = array;
    steps.push_back(tempArray); // Initial state
    int n = tempArray.size();

    // Use a gap sequence
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = tempArray[i];
            int j = i;

            // Swap elements and highlight
            while (j >= gap && tempArray[j - gap] > temp) {
                tempArray[j] = tempArray[j - gap];
                steps.push_back(tempArray); // Store each step

                // Highlight current and swapped indices
                highlights.append({j, j - gap});
                j -= gap;
            }
            tempArray[j] = temp; // Insert the temp element

            // Keep highlighting the inserted element
            highlights.append({j, i}); // Highlight the current insertion index
            steps.push_back(tempArray); // Store the state after insertion
        }
    }
    steps.push_back(tempArray); // Final state
}


// Bucket Sort
void SortingVisualizer::bucketSort() {
    if (array.isEmpty()) return;

    int maxValue = *std::max_element(array.begin(), array.end());
    QVector<QVector<int>> buckets(maxValue + 1);

    // Distribute elements into buckets
    for (int num : array) {
        buckets[num].append(num);
    }

    // Clear the original array to repopulate it from the buckets
    array.clear();
    for (int i = 0; i < buckets.size(); ++i) {
        if (!buckets[i].isEmpty()) {
            array.append(buckets[i]);
            steps.push_back(array); // Save the state after each bucket is processed
            highlights.append({i, -1}); // Highlight the current bucket index
        }
    }

    steps.push_back(array); // Store final state
}
