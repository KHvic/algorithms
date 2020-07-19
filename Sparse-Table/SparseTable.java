public class SparseTable {
    public static void main(String args[]) {
        int[] array = new int[]{4,6,7,5,7,3};
        int[][] minSparseTable = buildSparse(array);
        System.out.println(rangeQuery(minSparseTable,0,4));
        // printTable(minSparseTable);
    }
    public static int rangeQuery(int[][] sparse, int low, int high){
        int range = high-low+1;
        int p = (int)(Math.log(range)/Math.log(2));
        return Math.min(sparse[p][low],sparse[p][high-(1<<p)+1]);//1 full range from high
    }
    public static int[][] buildSparse(int[] array){
        int n = array.length;
        int m = (int)(Math.log(n)/Math.log(2)) + 1;
        int[][] sparse = new int[m][n];
        for(int i=0; i<n;i++) sparse[0][i] = array[i];
        for(int p=1; p<m;p++){
            int skipRange = 1 << (p-1);
            for(int i=0;i+skipRange*2<=n;i++) 
                sparse[p][i] = Math.min(sparse[p-1][i],sparse[p-1][i+skipRange]);
        }
        return sparse;
    }
    public static void printTable(int[][] table){
        for(int p=0;p<table.length;p++, System.out.println())
            for(int i=0;i<table[0].length;i++)
                System.out.print(table[p][i] + " ");
    }
}
