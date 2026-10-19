package model;

import java.util.*;

public class MyMap {

    private Map<Integer, List<Student>> map;

    public MyMap(){
        this.map = new TreeMap<>(new StudentGradeComparator());
    }

    private static class StudentGradeComparator implements Comparator<Integer> {
        @Override
        public int compare(Integer o1, Integer o2) {
            return o2.compareTo(o1);
        }
    }

    public void add(Student student){

        int key  = Math.round(student.getAverage());

        if(!map.containsKey(key)){
            map.put(key, new ArrayList<>());
        }
        map.get(key).add(student);
    }

   public Set<Map.Entry<Integer,List<Student>>> getEntries(){
        return map.entrySet();
   }
}
