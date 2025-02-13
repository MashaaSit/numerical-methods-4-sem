% Точное решение функции
y_exact = @(x) x.^2 .* exp(-x);

% Загрузка данных из файлов
data_adams_fixed_10 = load('/home/masha/numerical_methods/lab13 /lab13_proj/cmake-build-debug/adams_fixed_10.txt');
data_adams_fixed_100 = load('/home/masha/numerical_methods/lab13 /lab13_proj/cmake-build-debug/adams_fixed_100.txt');

% Создаем пустые массивы для данных адаптивного метода
x_adaptive = [];
y_adams_adaptive = [];
error_adaptive = [];
h_adaptive = [];

% Загружаем данные для разных значений eps
eps_values = [0.1, 0.01, 0.001, 0.0001, 1e-5, 1e-6, 1e-7];

% Инициализация массива для хранения максимальной погрешности
max_errors = zeros(size(eps_values));

for i = 1:length(eps_values)
    filename = sprintf('/home/masha/numerical_methods/lab13 /lab13_proj/cmake-build-debug/adams_%.8f.txt', eps_values(i));
    data_temp = dlmread(filename);
    x_adaptive = data_temp(:, 1); % Загружаем x для текущего eps
    y_euler_adaptive = data_temp(:, 2);
    error_adaptive = abs(data_temp(:, 2) - y_exact(data_temp(:, 1)));

    % Вычисляем и сохраняем шаг для текущего eps
    h_adaptive = data_temp(:,3);
    % Вычисляем максимальную погрешность и сохраняем
    max_errors(i) = max(error_adaptive);
end

% --- Построение графиков ---
##
##% 1. Точное и численные решения (фиксированный шаг N=10)
figure;
hold on;
plot(data_adams_fixed_10(:, 1), y_exact(data_adams_fixed_10(:, 1)), 'LineWidth', 1.5);
plot(data_adams_fixed_10(:, 1), data_adams_fixed_10(:, 2), '--', 'LineWidth', 1.5);
legend('Точное решение', 'Численное (N=10)');
xlim([1, 5]);
title('Точное и численные решения (Фиксированный шаг N=10)');
grid on;
xlabel('x');
ylabel('y');

##% 2. Точное и численные решения (фиксированный шаг N=100)
figure;
hold on;
plot(data_adams_fixed_100(:, 1), y_exact(data_adams_fixed_100(:, 1)), 'LineWidth', 1.5);
plot(data_adams_fixed_100(:, 1), data_adams_fixed_100(:, 2), '--', 'LineWidth', 1.5);
legend('Точное решение', 'Численное (N=100)');
xlim([1, 5]);
title('Точное и численные решения (Фиксированный шаг N=100)');
grid on;
xlabel('x');
ylabel('y');
####
######% 3. Графики ошибок для фиксированного шага N=10
figure;
hold on;
semilogy(data_adams_fixed_10(:, 1), abs(data_adams_fixed_10(:, 2) - y_exact(data_adams_fixed_10(:, 1))), 'LineWidth', 1.5);
xlim([1, 5]);
title('График ошибки (Фиксированный шаг N=10)');
xlabel('x');
ylabel('Погрешность');
grid on;
##
####% 4. Графики ошибок для фиксированного шага N=100
figure;
hold on;
semilogy(data_adams_fixed_100(:, 1), abs(data_adams_fixed_100(:, 2) - y_exact(data_adams_fixed_100(:, 1))), 'LineWidth', 1.5);
xlim([1, 5]);
title('График ошибки (Фиксированный шаг N=100)');
xlabel('x');
ylabel('Погрешность');
grid on;
##
####% 5. График изменения шага для eps = 1e-7
##figure;
##
##semilogy(x_adaptive, h_adaptive);
##xlim([1, 5])
##xlabel('x');
##ylabel('Шаг (h)');
##title('Изменение шага в адаптивном методе (eps = 1e-7)');
##grid on;
####
####% 5. График зависимости максимальной погрешности от заданной точности (эпсилон)
##figure;
##loglog(eps_values, max_errors, '-o', 'LineWidth', 1.5);
##xlim([10e-8, 0.1])
##xlabel('Заданная точность (eps)');
##ylabel('Максимальная погрешность');
##title('Зависимость максимальной погрешности от заданной точности');
##grid on

