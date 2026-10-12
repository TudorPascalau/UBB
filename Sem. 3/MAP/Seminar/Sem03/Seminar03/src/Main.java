import container.MyMap;
import model.Student;

import java.util.*;


public class Main {

    public static List<Student> getList() {
        List<Student> l = new ArrayList<>();
        l.add(new Student("Adam", 9.7f));
        l.add(new Student("Bob", 5.7f));
        l.add(new Student("Alice", 6.7f));
        l.add(new Student("Tom", 5.5f));
        l.add(new Student("Nico", 8.3f));
        return l;
    }

    public static void main(String[] args) {

        Student s1 = new Student("Dan", 4.5f);
        Student s2 = new Student("Ana", 8.5f);
        Student s3 = new Student("Dan", 4.5f);

        System.out.println(s1.equals(s2));

        System.out.println("Tree Set with base Student Comparable");
        Set<Student> studentSet = new HashSet<>();
        studentSet.add(s1);
        studentSet.add(s2);
        studentSet.add(s3);
        System.out.println("The size of the set:" + studentSet.size());
        for(Student student : studentSet) {
            System.out.println(student);
            System.out.println(student.hashCode());
        }

        Set<Student> treeSet = new TreeSet<>();
        treeSet.add(s1);
        treeSet.add(s2);
        treeSet.add(s3);
        for(Student student : treeSet) {
            System.out.println(student);
        }
        System.out.println("Tree Set with custom Comparator");
        Comparator<Student> medieComparator = new Comparator<Student>() {
            @Override
            public int compare(Student o1, Student o2) {
                return Float.compare(o1.getMedie(), o2.getMedie());
            }
        };

        Set<Student> medieSet = new TreeSet<>(medieComparator);
        medieSet.add(s1);
        medieSet.add(s2);
        medieSet.add(s3);
        for(Student student : medieSet) {
            System.out.println(student);
        }

        System.out.println("HashMap: ");
        Map<String,Student> map = new HashMap<>();
        map.put(s1.getNume(), s1);
        map.put(s2.getNume(), s2);
        map.put(s3.getNume(), s3);

        for(Map.Entry<String,Student> entry : map.entrySet()) {
            System.out.println("Key: " + entry.getKey());
            System.out.println("Value: " + entry.getValue());
        }

        System.out.println("TreeMap: ");
        TreeMap<String,Student> treeMap = new TreeMap<>();
        treeMap.put(s1.getNume(), s1);
        treeMap.put(s2.getNume(), s2);
        treeMap.put(s3.getNume(), s3);
        for(Map.Entry<String,Student> entry : treeMap.entrySet()) {
            System.out.println("Key: " + entry.getKey());
            System.out.println("Value: " + entry.getValue());
        }

        System.out.println("TreeMap with comparator: :");
        /// Trebuie construit comparator propriu care implementeaza => ramanem la Comparable
        Map<String,Student> medieMap = new TreeMap<>();

        System.out.println("MyMap: ");
        MyMap myMap = new MyMap();
        List<Student> l = getList();
        for(Student student : l) {
            myMap.add(student);
        }

        for(Map.Entry<Integer, List<Student>> entry : myMap.getEntries()) {
            for(Student student : entry.getValue()) {
                System.out.println(student);
            }
        }

    }
}
