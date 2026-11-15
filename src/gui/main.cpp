#include <QApplication>
#include <QFont>

#include "MainWindow.h"

// Start Qt and show the main StayNear window.
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setFont(QFont("Segoe UI", 10));
    app.setStyleSheet(R"(
        QWidget {
            color: #1e293b;
            font-family: "Segoe UI";
            font-size: 10pt;
        }
        QMainWindow, QDialog {
            background: #f4f7fb;
        }
        QLabel {
            background: transparent;
        }
        QLabel#brandMark {
            color: #ffffff;
            background: #2563eb;
            border-radius: 12px;
            font-size: 13pt;
            font-weight: 700;
        }
        QLabel#brandName {
            color: #0f172a;
            font-size: 15pt;
            font-weight: 700;
        }
        QLabel#brandTagline, QLabel#pageSubtitle, QLabel#helperText {
            color: #64748b;
        }
        QLabel#brandTagline, QLabel#metricCaption {
            font-size: 8pt;
            font-weight: 600;
        }
        QLabel#dialogTitle {
            color: #0f172a;
            font-size: 18pt;
            font-weight: 700;
        }
        QLabel#pageTitle {
            color: #0f172a;
            font-size: 25pt;
            font-weight: 700;
        }
        QLabel#sectionTitle {
            color: #0f172a;
            font-size: 12pt;
            font-weight: 700;
        }
        QLabel#connectionStatus {
            padding: 8px 12px;
            color: #166534;
            background: #dcfce7;
            border: 1px solid #bbf7d0;
            border-radius: 12px;
            font-size: 9pt;
            font-weight: 600;
        }
        QLabel#connectionStatus[offline="true"] {
            color: #92400e;
            background: #fef3c7;
            border-color: #fde68a;
        }
        QFrame#metricCard, QFrame#filterPanel {
            background: #ffffff;
            border: 1px solid #e2e8f0;
            border-radius: 12px;
        }
        QLabel#metricValue {
            color: #1d4ed8;
            font-size: 21pt;
            font-weight: 700;
        }
        QLabel#metricCaption {
            color: #64748b;
        }
        QLabel#resultCount {
            padding: 6px 11px;
            color: #1e40af;
            background: #dbeafe;
            border: 1px solid #bfdbfe;
            border-radius: 10px;
            font-size: 9pt;
            font-weight: 600;
        }
        QLabel#emptyState {
            padding: 24px;
            color: #64748b;
            background: #ffffff;
            border: 1px dashed #cbd5e1;
            border-radius: 12px;
            font-size: 11pt;
        }
        QLineEdit, QComboBox, QSpinBox, QDoubleSpinBox {
            min-height: 22px;
            padding: 7px 10px;
            background: #ffffff;
            border: 1px solid #cbd5e1;
            border-radius: 8px;
            selection-background-color: #bfdbfe;
        }
        QLineEdit:focus, QComboBox:focus, QSpinBox:focus, QDoubleSpinBox:focus {
            border: 1px solid #3b82f6;
        }
        QCheckBox {
            spacing: 8px;
        }
        QCheckBox::indicator {
            width: 17px;
            height: 17px;
        }
        QCheckBox::indicator:unchecked {
            background: #ffffff;
            border: 1px solid #94a3b8;
            border-radius: 4px;
        }
        QCheckBox::indicator:checked {
            background: #2563eb;
            border: 1px solid #2563eb;
            border-radius: 4px;
        }
        QPushButton {
            min-height: 22px;
            padding: 8px 14px;
            color: #334155;
            background: #ffffff;
            border: 1px solid #cbd5e1;
            border-radius: 8px;
            font-weight: 600;
        }
        QPushButton:hover {
            background: #eff6ff;
            border-color: #93c5fd;
        }
        QPushButton:pressed {
            background: #dbeafe;
        }
        QPushButton:disabled {
            color: #94a3b8;
            background: #f1f5f9;
        }
        QPushButton#primaryButton {
            color: #ffffff;
            background: #2563eb;
            border-color: #2563eb;
        }
        QPushButton#primaryButton:hover {
            background: #1d4ed8;
            border-color: #1d4ed8;
        }
        QPushButton#secondaryButton {
            color: #1e40af;
            background: #dbeafe;
            border-color: #bfdbfe;
        }
        QPushButton#textButton {
            min-height: 0;
            padding: 3px 5px;
            color: #2563eb;
            background: transparent;
            border: none;
        }
        QTableWidget#pgTable {
            background: #ffffff;
            alternate-background-color: #f8fafc;
            border: 1px solid #e2e8f0;
            border-radius: 10px;
            selection-background-color: #dbeafe;
            selection-color: #1e3a8a;
            outline: 0;
        }
        QTableWidget#pgTable::item {
            padding: 7px 8px;
            border-bottom: 1px solid #f1f5f9;
        }
        QTableWidget#pgTable::item:selected {
            background: #dbeafe;
            color: #1e3a8a;
        }
        QHeaderView::section {
            padding: 11px 8px;
            color: #475569;
            background: #f1f5f9;
            border: none;
            border-bottom: 1px solid #e2e8f0;
            font-size: 9pt;
            font-weight: 600;
        }
        QGroupBox {
            margin-top: 12px;
            padding: 14px 12px 10px;
            color: #0f172a;
            background: #ffffff;
            border: 1px solid #e2e8f0;
            border-radius: 10px;
            font-weight: 700;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 12px;
            padding: 0 5px;
        }
        QTextEdit {
            background: #ffffff;
            border: 1px solid #e2e8f0;
            border-radius: 9px;
            padding: 10px;
        }
    )");

    MainWindow window;
    window.show();

    return app.exec();
}
