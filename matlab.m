% --- Основной код скрипта ---

% Загрузка данных из файлов
data_mkr_10 = load('/home/masha/numerical_methods/lab14/lab_14_proj/cmake-build-debug/results_1000.txt');
data_mkr_100 = load('/home/masha/numerical_methods/lab14/lab_14_proj/cmake-build-debug/results_100.txt');

% Создаем пустые массивы для данных адаптивного метода
x_adaptive = [];
y_mkr_adaptive = [];
error_adaptive = [];
h_adaptive = [];

% Загружаем данные для разных значений eps
eps_values = [0.1, 0.01, 0.001, 0.0001, 1e-5, 1e-6, 1e-7];

% Инициализация массива для хранения максимальной погрешности
##max_errors = zeros(size(eps_values));
##for i = 1:length(eps_values)
##    filename = sprintf('/home/masha/numerical_methods/lab14/lab_14_proj/cmake-build-debug/eps_e-%d.txt', i);
##    data_temp = load(filename);
##    x_adaptive = data_temp(:, 1); % Загружаем x для текущего eps
##    y_mkr_adaptive = data_temp(:, 2);
##
##    % Вычисляем ошибку
##    error_adaptive = abs(data_temp(:, 2) - exact_solution(data_temp(:, 1)));
##
##    % Вычисляем и сохраняем шаг для текущего eps
##    h_temp = diff(x_adaptive);
##    h_adaptive = [h_temp; NaN]; % Дополняем NaN для согласования размерностей
##
##    % Вычисляем максимальную погрешность и сохраняем
##    max_errors(i) = max(error_adaptive);
##end

% --- Построение графиков ---
x = 0:0.1:1; % Создание вектора x от 0 до 1 с шагом 0.1
y = exact_solution(x); % Вычисление значений y с помощью функции
plot(x, y); % Построение графика
title('График точного решения');
xlabel('x');
ylabel('y(x)');
grid on;
% 1. Точное и численные решения (фиксированный шаг)
##figure;
##hold on;
##plot(data_mkr_10(:, 1), exact_solution(data_mkr_10(:, 1)), 'LineWidth', 1.5);
##plot(data_mkr_10(:, 1), data_mkr_10(:, 2), '--', 'LineWidth', 1.5);
##legend('Точное решение', 'Численное (N=10)');
##xlim([0, 1]);
##title('Точное и численные решения (Фиксированный шаг N=10)')
##grid on;
##
##figure;
##hold on;
##plot(data_mkr_100(:, 1), exact_solution(data_mkr_100(:, 1)), 'LineWidth', 1.5);
##plot(data_mkr_100(:, 1), data_mkr_100(:, 2), '--', 'LineWidth', 1.5);
##legend('Точное решение', 'Численное (N=100)');
##xlim([0, 1]);
##title('Точное и численные решения (Фиксированный шаг N=100)')
##grid on;

##% 3. Графики ошибок для фиксированного шага N=10
##figure;
##hold on;
##plot(data_mkr_10(:, 1), abs(data_mkr_10(:, 2) - exact_solution(data_mkr_10(:, 1))), 'LineWidth', 1.5);
##xlim([0, 1]);
##title('Графики ошибок для фиксированного шага N=10')
##xlabel('x');
##ylabel('Погрешность');
##grid on;
##
##% 4. Графики ошибок для фиксированного шага N=100
##figure;
##hold on;
##plot(data_mkr_100(:, 1), abs(data_mkr_100(:, 2) - exact_solution(data_mkr_100(:, 1))), 'LineWidth', 1.5);
##xlim([0, 1]);
##title('Графики ошибок для фиксированного шага N=100')
##xlabel('x');
##ylabel('Погрешность');
##grid on;
##
##% 5. График изменения шага для адаптивного метода
##figure;
##semilogy(x_adaptive(1:end-1), h_adaptive(1:end-1));
##xlabel('x');
##ylabel('Шаг (h)');
##title('Изменение шага в методе конечных разностей (1 порядок)');
##grid on;
##
##% 6. График зависимости максимальной погрешности от заданной точности (эпсилон)
##figure;
##loglog(eps_values, max_errors, '-o', 'LineWidth', 1.5);
##xlim([10e-8, 0.1])
##xlabel('Заданная точность (eps)');
##ylabel('Максимальная погрешность');
##title('Зависимость максимальной погрешности от заданной точности');
##grid on;

