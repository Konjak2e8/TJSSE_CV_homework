# Assignment 2

1. let $p(x,y,w)$ be the infinite point of this line.

   for $p$, we have $x-3y+4w=0$

   let $w=0$, then $x-3y=0$, the coordinate of $p$ is $(1,-3)$.

   the homogeneous coordinate of $p$ is $(1,-3,0)$.

2. $x_d=x(1+k_1x^2+k_1y^2+k_2x^4+k_2y^4+2k_2x^2y^2)+2\rho_1xy+\rho_2(y^2+3x^2)+k_3 (x^7+3x^3y^4+3x^5y^2+xy^6)$

   $y_d=y(1+k_1x^2+k_1y^2+k_2x^4+k_2y^4+2k_2x^2y^2)+2\rho_2xy+\rho_1(x^2+3y^2)+k_3 (y^7+3x^4y^3+3x^2y^5+yx^6)$

   $\frac{dx_d}{dx}=6\rho_2x+(3k_1+6k_2y^2+9k_3y^4)x^2+(5k_2+15k_3y^2)x^4+7k_3x^6+2\rho_1y+k_3y^6+1$

   $\frac{dx_d}{dy}=2k_1xy+4k_2xy^3+4k_2x^3y+5k_2y^4+6k_2x^2y^2+2\rho_2x+\$ 
   $$
   \begin{aligned}
   \frac{dp_d}{dp_n^T}&=\begin{bmatrix}\frac{dx_d}{dx}&\frac{dx_d}{dy}\\\frac{dy_d}{dx}&\frac{dy_d}{dy}\end{bmatrix} \\
   &=\begin{bmatrix}1+k_1r^2+k_2r^4+2\rho_1y+4\rho_2x+k_3r^6&2\rho_1x\\2\rho_2y&1+k_1r^2+k_2r^4+2\rho_2x+4\rho_1y+k_3r^6\end{bmatrix}
   \end{aligned}
   $$

3. 
   $$
   \mathbf{R}=\beta\mathbf{I}+(1-\beta)\mathbf{nn^T}+\alpha\mathbf{n\textasciicircum}
   $$

2. 

