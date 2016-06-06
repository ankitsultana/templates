import java.util.*;
import java.io.*;

class Solution {
    // @Test
    public void testLisNumberAndLength(List<Integer> x) {

        List<Integer> input = Arrays.asList(16, 5, 8, 6, 1, 10, 5, 2, 15, 3, 2, 4, 1);
        int[] result = this.lisNumberAndlength(x);
        System.out.println(String.format(
                "This sequence has %s longest increasing subsequenses of length %s", 
                result[0], result[1]
                ));
    }

    public static void main(String[] args) {
        Solution inst = new Solution();
        List<Integer> x = new ArrayList<Integer>();
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        for(int i = 0; i < n; i++) {
            int temp = sc.nextInt();
            x.add(temp);
        }
        inst.testLisNumberAndLength(x);
    }


    /**
     * Body of improved LIS algorithm
     */
    public <T extends Comparable<T>> int[] lisNumberAndlength(List<T> input) {

        if (input.size() == 0) 
            return new int[] {0, 0};

        List<List<Sub<T>>> subs = new ArrayList<>();
        List<Sub<T>> tails = new ArrayList<>();

        for (T e : input) {
            int pos = search(tails, new Sub<>(e, 0), false);      // row for a new sub to be placed
            int sum = 1;
            if (pos > 0) {
                List<Sub<T>> pRow = subs.get(pos - 1);            // previous row
                int index = search(pRow, new Sub<T>(e, 0), true); // index of most left element that <= e
                if (pRow.get(index).value.compareTo(e) < 0) {
                    index--;
                } 
                sum = pRow.get(pRow.size() - 1).sum;              // sum of tail element in previous row
                if (index >= 0) {
                    sum -= pRow.get(index).sum;
                }
            }

            if (pos >= subs.size()) {                             // add a new row
                List<Sub<T>> row = new ArrayList<>();
                row.add(new Sub<>(e, sum));
                subs.add(row);
                tails.add(new Sub<>(e, 0));

            } else {                                              // add sub to existing row
                List<Sub<T>> row = subs.get(pos);
                Sub<T> tail = row.get(row.size() - 1); 
                if (tail.value.equals(e)) {
                    tail.sum += sum;
                } else {
                    row.add(new Sub<>(e, tail.sum + sum));
                    tails.set(pos, new Sub<>(e, 0));
                }
            }
        }

        List<Sub<T>> lastRow = subs.get(subs.size() - 1);
        Sub<T> last = lastRow.get(lastRow.size() - 1);
        return new int[]{last.sum, subs.size()};
    }



    /**
     * Implementation of binary search in a sorted list
     */
    public <T> int search(List<? extends Comparable<T>> a, T v, boolean reversed) {

        if (a.size() == 0)
            return 0;

        int sign = reversed ? -1 : 1;
        int right = a.size() - 1;

        Comparable<T> vRight = a.get(right);
        if (vRight.compareTo(v) * sign < 0)
            return right + 1;

        int left = 0;
        int pos = 0;
        Comparable<T> vPos;
        Comparable<T> vLeft = a.get(left);

        for(;;) {
            if (right - left <= 1) {
                if (vRight.compareTo(v) * sign >= 0 && vLeft.compareTo(v) * sign < 0) 
                    return right;
                else 
                    return left;
            }
            pos = (left + right) >>> 1;
            vPos = a.get(pos);
            if (vPos.equals(v)) {
                return pos;
            } else if (vPos.compareTo(v) * sign > 0) {
                right = pos;
                vRight = vPos;
            } else {
                left = pos;
                vLeft = vPos;
            }
        } 
    }



    /**
     * Class for 'sub' pairs
     */
    public static class Sub<T extends Comparable<T>> implements Comparable<Sub<T>> {

        T value;
        int sum;

        public Sub(T value, int sum) { 
            this.value = value; 
            this.sum = sum; 
        }

        @Override public String toString() {
            return String.format("(%s, %s)", value, sum); 
        }

        @Override public int compareTo(Sub<T> another) { 
            return this.value.compareTo(another.value); 
        }
    }
}
