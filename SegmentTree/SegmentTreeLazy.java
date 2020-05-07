import java.util.Arrays;

// Segment Tree with lazy propagation range update
public class SegmentTreeLazy{
    static int[] segmentTree;
    static int[] lazy;
    static int size = 0;

    public static void main(String []args){
        int[] arr = new int[]{2,5,8,5,2,3,7,11,3,4};
        init(arr);

        int queryLow = 0;
        int queryHigh = size-1;
        System.out.println(queryMax(queryLow, queryHigh));
        update(3, 20);
        System.out.println(queryMax(1, 5));
    }
    public static void init(int[] arr) {
        size = arr.length;
        // size of segmentTree = 2*2^Ceil(Log_{2}(N))-1, 2^Ceil(Log_{2}(N)) is the next larger in pow2
        // we can also do it in O(1) using bit manipulation
        int nextPow2 = (int)Math.ceil(Math.log(size)/Math.log(2)); // get ceil pow
        nextPow2 = (int)Math.pow(2,nextPow2);
        segmentTree = new int[2*nextPow2-1];
        lazy = new int[segmentTree.length];
        Arrays.fill(lazy, -1);
        constructTree(arr,0,arr.length-1,0);
    }

    public static void constructTree(int[] arr, int low, int high, int idx){
        if(low == high) {
            segmentTree[idx] = arr[low];
            return;
        }
        int mid = (low+high)/2;
        constructTree(arr,low,mid,idx*2+1);
        constructTree(arr,mid+1,high,idx*2+2);
        segmentTree[idx] = Math.max(segmentTree[idx*2+1],segmentTree[idx*2+2]);
    }
    public static int queryMax(int queryLow, int queryHigh){
        return query(0,size-1,queryLow,queryHigh,0);
    }
    public static int query(int low, int high, int qlow, int qhigh, int idx){
        updateLazy(idx,low,high);
        // full overlap - query range is within low and high
        if(low >= qlow && high <= qhigh){
            return segmentTree[idx];
        }
        // no overlap
        else if(qhigh < low || qlow > high){
            return Integer.MIN_VALUE;
        }
        // partial overlap
        int mid = (low+high)/2;
        int leftRes = query(low,mid,qlow,qhigh,idx*2+1);
        int rightRes = query(mid+1,high,qlow,qhigh,idx*2+2);
        return Math.max(leftRes,rightRes);
    }

    public static void update(int i, int val) {
        updateRange(0, 0, size, i, i, val);
    }

    public static void updateRange(int idx, int low, int high, int qlow, int qhigh, int val){
        updateLazy(idx,low,high);
        // no overlap
        if(qlow > high || qhigh < low) return;
            // full overlap
        else if(qlow <= low && high <= qhigh) {
            lazy[idx] = val;
            updateLazy(idx, low, high);
            // partial overlap
        } else {
            int mid = (low+high)/2;
            updateRange(idx*2+1, low , mid, qlow, qhigh, val);
            updateRange(idx*2+2, mid+1, high, qlow, qhigh, val);
            segmentTree[idx] = Math.max(segmentTree[idx*2+1], segmentTree[idx*2+2]);
        }
    }

    public static void updateLazy(int idx, int low, int high){
        // apply lazy to child if not leaf & has lazy
        if(lazy[idx] != -1 && low != high){
            lazy[idx*2+1] = lazy[idx];
            lazy[idx*2+2] = lazy[idx];
        }
        if(lazy[idx] != -1) segmentTree[idx] = lazy[idx];
        lazy[idx] = -1; // clear lazy
    }
}
