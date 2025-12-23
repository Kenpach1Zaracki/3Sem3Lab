#!/bin/bash

# Скрипт для генерации UML диаграмм из PlantUML файла

echo "Генерация UML диаграмм..."

# Проверяем наличие curl
if ! command -v curl &> /dev/null; then
    echo "Ошибка: curl не установлен. Установите его: sudo apt-get install curl"
    exit 1
fi

# Создаем директорию для изображений
mkdir -p uml_images

echo "Используем онлайн сервис PlantUML для генерации изображений..."

# Кодируем PlantUML файл в формат для онлайн сервиса
# PlantUML онлайн API требует специального кодирования

# Функция для генерации диаграммы через онлайн сервис
generate_diagram() {
    local input_file="$1"
    local output_file="$2"

    # Используем публичный PlantUML сервер
    # Сначала кодируем содержимое файла
    encoded=$(curl -s -X POST --data-binary @"$input_file" https://www.plantuml.com/plantuml/png/)

    # Альтернативный метод: используем lokkal PlantUML если установлен
    if command -v plantuml &> /dev/null; then
        echo "Найден локальный PlantUML, используем его..."
        plantuml -tpng "$input_file" -o uml_images
        echo "✓ Диаграмма сгенерирована: uml_images/$(basename ${input_file%.puml}.png)"
    else
        echo "PlantUML не установлен локально."
        echo "Для генерации изображений:"
        echo "1. Установите PlantUML: sudo apt-get install plantuml"
        echo "2. Или используйте онлайн: https://www.plantuml.com/plantuml/uml/"
        echo "3. Или скопируйте содержимое uml_diagrams.puml на сайт https://plantuml.com/"
    fi
}

echo ""
echo "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "="
echo "ИНСТРУКЦИЯ ПО ГЕНЕРАЦИИ ДИАГРАММ:"
echo "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "="
echo ""
echo "Вариант 1: Онлайн генерация (РЕКОМЕНДУЕТСЯ)"
echo "  1. Откройте https://www.plantuml.com/plantuml/uml/"
echo "  2. Скопируйте содержимое файла uml_diagrams.puml"
echo "  3. Вставьте в онлайн редактор"
echo "  4. Нажмите 'Submit' для просмотра"
echo "  5. Скачайте изображение (PNG, SVG, или PDF)"
echo ""
echo "Вариант 2: Установка PlantUML локально"
echo "  sudo apt-get update"
echo "  sudo apt-get install plantuml"
echo "  plantuml -tpng uml_diagrams.puml -o uml_images"
echo ""
echo "Вариант 3: Mermaid диаграммы (УЖЕ ГОТОВО!)"
echo "  Откройте файл UML_Diagrams.md:"
echo "  - На GitHub (диаграммы отобразятся автоматически)"
echo "  - Или скопируйте код на https://mermaid.live"
echo "  - Или откройте в VS Code с расширением 'Markdown Preview Mermaid Support'"
echo ""
echo "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "=" "="

# Если PlantUML установлен, генерируем
if command -v plantuml &> /dev/null; then
    echo ""
    echo "Генерирую изображения с помощью PlantUML..."
    plantuml -tpng uml_diagrams.puml -o uml_images
    echo "✓ Готово! Изображения сохранены в директории uml_images/"
else
    echo ""
    echo "⚠ PlantUML не установлен. Используйте онлайн сервис или установите PlantUML."
    echo ""
    echo "Для Mermaid диаграмм просто откройте UML_Diagrams.md!"
fi
