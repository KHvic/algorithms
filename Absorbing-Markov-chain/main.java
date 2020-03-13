import java.util.ArrayList;
import java.util.List;

class Main {
    // take in occurence count of going from states a to states b
    // return FR matrix, probability of going from a terminal to nonterminal state
    public static double[][] solve(int[][] m) {
        List<Integer> terminal = new ArrayList<>();
        List<Integer> nonterminal = new ArrayList<>();
        double[][] probMat = computeProbMat(m, terminal, nonterminal);

        // Q matrix is the probability submatrix from nonterminal to terminal
        double[][] R = getSubMat(probMat, nonterminal, terminal);
        // R matrix is the probability submatrix from  nonterminal to nonterminal
        double[][] Q = getSubMat(probMat, nonterminal, nonterminal);

        // F = (I-Q)^-1
        double[][] F = computeF(Q);

        return multiply(F, R);
    }

    public static double[][] multiply(double[][] F, double[][] R) {
        int n = F.length, m = R[0].length;
        double[][] FR = new double[n][m];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < F[0].length; k++) {
                    FR[i][j] += F[i][k] * R[k][j];
                }
            }
        }

        return FR;
    }

    public static double[][] computeProbMat(int[][] m, List<Integer> terminal, List<Integer> nonterminal) {
        int n = m.length;
        // compute transition matrix
        double[][] probmat = new double[n][n];
        for (int i = 0; i < n; i++) {
            int sum = 0;
            for (int j = 0; j < n; j++) {
                sum += m[i][j];
            }
            // is terminal if cannot reach other state
            if (sum - m[i][i] == 0) {
                terminal.add(i);
                probmat[i][i] = 1;
            } else {
                nonterminal.add(i);
                for (int j = 0; j < n; j++) {
                    probmat[i][j] = (double) m[i][j] / sum;
                }
            }
        }
        return probmat;
    }

    public static double[][] getSubMat(double[][] probMat, List<Integer> from, List<Integer> to) {
        double[][] submat = new double[from.size()][to.size()];
        for (int i = 0; i < from.size(); i++) {
            for (int j = 0; j < to.size(); j++) {
                submat[i][j] = probMat[from.get(i)][to.get(j)];
            }
        }
        return submat;
    }

    public static double[][] computeF(double[][] Q) {
        // I - Q
        double[][] iMinusQ = new double[Q.length][Q[0].length];
        for (int i = 0; i < Q.length; i++) {
            for (int j = 0; j < Q[0].length; j++) {
                iMinusQ[i][j] = -Q[i][j];
                if (i == j) iMinusQ[i][j] += 1.0;
            }
        }

        // inverse
        return invert(iMinusQ);
    }

    public static int[] decimalToFraction(double dec) {
        double tolerance = 1.0E-6;
        double h1 = 1;
        double h2 = 0;
        double k1 = 0;
        double k2 = 1;
        double b = dec;
        do {
            double a = Math.floor(b);
            double aux = h1;
            h1 = a * h1 + h2;
            h2 = aux;
            aux = k1;
            k1 = a * k1 + k2;
            k2 = aux;
            b = 1 / (b - a);
        } while (Math.abs(dec - h1 / k1) > dec * tolerance);

        int[] fraction = new int[2];
        fraction[0] = (int) h1;
        fraction[1] = (int) k1;
        return fraction;
    }

    // inverse matrix program from sanfoundry.com
    public static double[][] invert(double a[][]) {
        int n = a.length;
        double x[][] = new double[n][n];
        double b[][] = new double[n][n];
        int index[] = new int[n];
        for (int i = 0; i < n; ++i)
            b[i][i] = 1;

        // Transform the matrix into an upper triangle
        gaussian(a, index);

        // Update the matrix b[i][j] with the ratios stored
        for (int i = 0; i < n - 1; ++i)
            for (int j = i + 1; j < n; ++j)
                for (int k = 0; k < n; ++k)
                    b[index[j]][k]
                            -= a[index[j]][i] * b[index[i]][k];

        // Perform backward substitutions
        for (int i = 0; i < n; ++i) {
            x[n - 1][i] = b[index[n - 1]][i] / a[index[n - 1]][n - 1];
            for (int j = n - 2; j >= 0; --j) {
                x[j][i] = b[index[j]][i];
                for (int k = j + 1; k < n; ++k) {
                    x[j][i] -= a[index[j]][k] * x[k][i];
                }
                x[j][i] /= a[index[j]][j];
            }
        }
        return x;
    }

    // Gaussian Elimination program from sanfoundry.com
    public static void gaussian(double a[][], int index[]) {
        int n = index.length;
        double c[] = new double[n];
        for (int i = 0; i < n; ++i)
            index[i] = i;
        for (int i = 0; i < n; ++i) {
            double c1 = 0;
            for (int j = 0; j < n; ++j) {
                double c0 = Math.abs(a[i][j]);
                if (c0 > c1) c1 = c0;
            }
            c[i] = c1;
        }
        int k = 0;
        for (int j = 0; j < n - 1; ++j) {
            double pi1 = 0;
            for (int i = j; i < n; ++i) {
                double pi0 = Math.abs(a[index[i]][j]);
                pi0 /= c[index[i]];
                if (pi0 > pi1) {
                    pi1 = pi0;
                    k = i;
                }
            }
            int itmp = index[j];
            index[j] = index[k];
            index[k] = itmp;
            for (int i = j + 1; i < n; ++i) {
                double pj = a[index[i]][j] / a[index[j]][j];
                a[index[i]][j] = pj;
                for (int l = j + 1; l < n; ++l)
                    a[index[i]][l] -= pj * a[index[j]][l];
            }
        }
    }
}