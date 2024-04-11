$J(x)$ is the Jacobian matrix and $\mu>0$ .
$$
dL=J(x)^Tf(x)+J(x)^TJ(x)h+\mu h
$$
So $L(h)$ is differentiable up to first order.
$$
d^2L=J(x)^TJ(x)+\mu I,\ I\in\mathbb{R}^n
$$
So $L(h)$ is differentiable up to second order.

The Hessian matrix of $L(h)$ is $J(x)^TJ(x)$, noted as $H$.

$\forall x\neq0$, we have 
$$
x^THx=x^TJ(x)^TJ(x)x=||xJ(x)||^2\geq0
$$


So $H$ is semi-positive definite.

For all eigenvalues $\lambda_i(\lambda_i\geq0,i=1,2,...,n)$ of $H$, we have $Hv_i=\lambda_iv_i$
$$
(H+\mu I)v_i=(\lambda_i+\mu)v_i
$$
So all eigenvalues of $(A+\mu I)$, which are $\{\lambda_i+\mu\}$ are positive.

So $A+\mu I$ is positive definite.

If a function $L(h)$ is  differentiable up to at least second order, $L$ is strictly convex if its Hessian matrix is positive definite.

Therefore, $L$ is strictly convex.