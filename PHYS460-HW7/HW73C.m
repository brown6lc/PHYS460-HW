%% =========================================
%  Parameters
%% =========================================
a = 1;
h = 1;

nValues = [1, 2, 5, 10];

%% =========================================
%  |Phi_n(p,t)|^2 Definition
%% =========================================

probDensity = @(p, n) (4*pi*a*n^2/h) .* ...
    (mod(n,2)==1) .* cos(p*a/(2*h)).^2 ./ ((p*a/h).^2 - (n*pi)^2).^2 + ...
    (4*pi*a*n^2/h) .* ...
    (mod(n,2)==0) .* sin(p*a/(2*h)).^2 ./ ((p*a/h).^2 - (n*pi)^2).^2;

%% =========================================
%  Custom Peak Finder (no toolbox needed)
%% =========================================

function [peak_vals, peak_locs] = findPeaksCustom(x, y, minProminence)
    peak_vals = [];
    peak_locs = [];
    for k = 2:length(y)-1
        if y(k) > y(k-1) && y(k) > y(k+1) && y(k) > minProminence
            peak_vals(end+1) = y(k);
            peak_locs(end+1) = k;
        end
    end
end

%% =========================================
%  Plot |Phi_n(p,t)|^2 for each n
%% =========================================

colors = lines(length(nValues));
figure('Name','Momentum Probability Density','NumberTitle','off','Color','w');

for i = 1:length(nValues)
    n  = nValues(i);
    p1 = n * pi * h / a;

    % Fine p-grid avoiding singularities
    p_left   = linspace(-4*p1, -p1-0.01, 3000);
    p_middle = linspace(-p1+0.01, p1-0.01, 6000);
    p_right  = linspace( p1+0.01,  4*p1,  3000);
    p_full   = [p_left, p_middle, p_right];

    % Evaluate and clip spikes
    rho = probDensity(p_full, n);
    rho(rho < 0 | rho > 5) = nan;

    subplot(2, 2, i);
    plot(p_full, rho, 'Color', colors(i,:), 'LineWidth', 2);
    hold on;

    % ---- Find peaks in middle region ----
    p_search   = linspace(-p1+0.05, p1-0.05, 100000);
    rho_search = probDensity(p_search, n);
    rho_search(rho_search < 0 | isnan(rho_search)) = 0;

    minProm = max(rho_search) * 0.05;
    [pks, locs] = findPeaksCustom(p_search, rho_search, minProm);

    % Mark peaks
    for j = 1:length(locs)
        xp = p_search(locs(j));
        yp = pks(j);
        plot(xp, yp, 'rv', 'MarkerFaceColor', 'r', 'MarkerSize', 9);
        text(xp, yp*1.08, sprintf('p=%.2f', xp), ...
             'HorizontalAlignment','center','FontSize',8,'Color','r');
    end

    % Singularity markers
    xline( p1, 'k--', 'LineWidth', 1.2);
    xline(-p1, 'k--', 'LineWidth', 1.2);

    if mod(n,2)==1
        titleStr = sprintf('n = %d  (odd, cos²)', n);
    else
        titleStr = sprintf('n = %d  (even, sin²)', n);
    end

    title(titleStr, 'FontSize', 12, 'FontWeight', 'bold');
    xlabel('p',               'FontSize', 11);
    ylabel('|\Phi_n(p,t)|^2', 'FontSize', 11);
    xlim([-4*p1, 4*p1]);
    ylim([0, inf]);
    grid on; box on;
    hold off;
end

sgtitle('Momentum Probability Density |\Phi_n(p,t)|^2  for  n = 1, 2, 5, 10', ...
        'FontSize', 14, 'FontWeight', 'bold');

%% =========================================
%  Print most probable momenta to console
%% =========================================

fprintf('-----------\n')
fprintf('  n  |  most probable momentum\n')
fprintf('-----------\n')

for i = 1:length(nValues)
    n  = nValues(i);
    p1 = n * pi * h / a;

    p_search   = linspace(-p1+0.05, p1-0.05, 100000);
    rho_search = probDensity(p_search, n);
    rho_search(rho_search < 0 | isnan(rho_search)) = 0;

    minProm = max(rho_search) * 0.05;
    [~, locs] = findPeaksCustom(p_search, rho_search, minProm);
    peak_p = p_search(locs);

    fprintf(' n=%-2d |  p* = [ ', n);
    fprintf('%+.4f  ', peak_p);
    fprintf(']\n');
end

fprintf('-----------\n')

fprintf('\n large n \n')
for i = 1:length(nValues)
    n = nValues(i);
    fprintf(' n=%-2d | Classical p = +/-%.4f\n', n, n*pi*h/a);
end