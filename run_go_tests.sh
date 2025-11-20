#!/usr/bin/env bash
set -e

cd "$(dirname "$0")/golang"

echo "== Запуск тестов с покрытием =="
go test ./... -coverprofile=coverage.out

echo "== Генерация HTML-отчёта =="
go tool cover -html=coverage.out -o coverage.html

echo "Готово. Открой файл golang/coverage.html в браузере."
