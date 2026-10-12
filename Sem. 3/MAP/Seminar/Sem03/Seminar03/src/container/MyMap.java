package container;

import model.Student;

import java.util.*;

public class MyMap {

    private static class GradeComparator implements Comparator<Integer> {
        @Override
        public int compare(Integer o1, Integer o2) {
            return o2.compareTo(o1);
        }
    };

    private Map<Integer, List<Student>> map;

    public MyMap() {
        this.map = new TreeMap<>(new GradeComparator());
    }

    public void add(Student student) {
        int medie = Math.round(student.getMedie());

        if(!map.containsKey(medie)) {
            List<Student> list = new ArrayList<Student>();
            list.add(student);
            map.put(medie, list);
        }
        else {
            List<Student> list = map.get(medie);
            list.add(student);
        }
    }


    public Set<Map.Entry<Integer, List<Student>>> getEntries(){
        return map.entrySet();
    }
}
