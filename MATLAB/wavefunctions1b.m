%constants
m = 1;
omega = 1;
hbar = 1;

%wavefunctions
psi0 = @(x) (m*omega/(pi*hbar))^(1/4) * exp(-m*omega*x.^2/(2*hbar));
psi1 = @(x) (m*omega/(pi*hbar))^(1/4) * sqrt(2*m*omega/hbar) .* x .* exp(-m*omega*x.^2/(2*hbar));
psi2 = @(x) (m*omega/(pi*hbar))^(1/4) * (1/sqrt(2)) * (2*m*omega/hbar * x.^2 - 1) .* exp(-m*omega*x.^2/(2*hbar));

%classical turning points x0 = sqrt((2n+1)*hbar/m*omega)
x0_0 = sqrt(1*hbar/(m*omega));
x0_1 = sqrt(3*hbar/(m*omega));
x0_2 = sqrt(5*hbar/(m*omega));

%probabilities in forbidden region P = 2 * integral from x0 to inf
P0 = 2 * integral(@(x) abs(psi0(x)).^2, x0_0, inf);
P1 = 2 * integral(@(x) abs(psi1(x)).^2, x0_1, inf);
P2 = 2 * integral(@(x) abs(psi2(x)).^2, x0_2, inf);

fprintf('n=0: %.3f\n', P0)
fprintf('n=1: %.3f\n', P1)
fprintf('n=2: %.3f\n', P2)
