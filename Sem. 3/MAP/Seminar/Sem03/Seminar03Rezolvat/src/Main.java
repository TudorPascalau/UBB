import model.MyMap;
import model.Student;
import repository.InMemoryRepository;
import repository.Repository;
import java.util.*;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {

    public static List<Student> getList() {
        List<Student> l = new ArrayList<Student>();
        l.add(new Student("Bob", 9.7f));
        l.add(new Student("Ana", 7.3f));
        l.add(new Student("Tom", 6f));
        l.add(new Student("Michael", 6.9f));
        l.add(new Student("Andrew", 9.5f));
        l.add(new Student("Daniel", 9.9f));
        return l;
    }

    private static List<Student> getListStudents() {
        return List.of(
                new Student(1, "2", 7.3f),
                new Student(2, "3", 6f),
                new Student(3, "4", 6.9f),
                new Student(4, "5", 9.5f),
                new Student(5, "6", 9.9f),
                new Student(6, "1", 9.7f)
        );
    }

    public static void main(String[] args) {

        Student s1 = new Student("Dan", 4.5f);
        Student s2 = new Student ("Ana", 8.5f);
        Student s3 = new Student ("Dan",4.5f);

        System.out.println(s1);
        System.out.println(s1.equals(s3));
        System.out.println(s1.hashCode());
        System.out.println(s3.hashCode());
        System.out.println(s1.hashCode() == s3.hashCode());

        System.out.println("Hash Set");
        Set<Student> students = new HashSet<>();

        students.add(s1);
        students.add(s2);
        students.add(s3);

        for(Student s: students){
            System.out.println(s);
        }

        System.out.println(students.contains(new Student("Dan", 4.5f)));

        System.out.println("Tree Set");
        Set<Student> treeSet = new TreeSet<>();
        treeSet.add(s1);
        treeSet.add(s2);
        treeSet.add(s3);
        for(Student s: treeSet){
            System.out.println(s);
        }
        System.out.println("Number of students in the tree set:"+treeSet.size());

        System.out.println("Tree set with comparator");
        Comparator<Student> comparator = new Comparator<Student>() {
            @Override
            public int compare(Student o1, Student o2) {
                return o1.getName().compareTo(o2.getName());
            }
        };
        TreeSet<Student>treeSetWithComparator  = new TreeSet<>(comparator);
        treeSetWithComparator.add(s1);
        treeSetWithComparator.add(s2);
        treeSetWithComparator.add(s3);
        for(Student s: treeSetWithComparator){
            System.out.println(s);
        }

        Comparator<Student>gradesComparator = new Comparator<Student>() {
            @Override
            public int compare(Student o1, Student o2) {
                return Float.compare(o2.getAverage(), o1.getAverage());
            }
        };

        Set<Student>treeSetGrades = new TreeSet<>(gradesComparator);
        treeSetGrades.add(s1);
        treeSetGrades.add(s2);
        treeSetGrades.add(s3);
        System.out.println("Tree set with grades comparator");

        for(Student s: treeSetGrades){
            System.out.println(s);
        }

        Map<String, Student> map = new HashMap<>();
        map.put(s1.getName(), s1);
        map.put(s2.getName(), s2);
        map.put(s3.getName(), s3);

        System.out.println("Hash Map");
        for(Map.Entry<String, Student> entry: map.entrySet()){
            System.out.println(entry);
        }

        System.out.println("Tree Map");
        Map<String, Student> treeMap = new TreeMap<>();
        treeMap.put(s1.getName(), s1);
        treeMap.put(s2.getName(), s2);
        treeMap.put(s3.getName(), s3);
        for(Map.Entry<String, Student> entry: treeMap.entrySet()){
            System.out.println(entry);
        }

        List<Student> list = new ArrayList<>();
        list.add(s1);
        list.add(s2);
        list.add(s3);

//        Collections.sort(list, new Comparator<Student>() {
//            @Override
//            public int compare(Student o1, Student o2) {
//                return Float.compare(o1.getAverage(), o2.getAverage());
//            }
//        });

        Collections.sort(list);

        for(Student s: list){
            System.out.println(s);
        }

        Iterator<Student>iterator  = list.iterator();

        System.out.println("Iterator:");
        while(iterator.hasNext()){
            System.out.println(iterator.next());
        }

        MyMap myMap = new MyMap();
        List<Student> l = getList();
        for(Student s: l){
            myMap.add(s);
        }

        for(Map.Entry<Integer,List<Student>> entry: myMap.getEntries()){
            System.out.println("Students with grade:"+entry.getKey());
            List<Student> studentsWithGrades = entry.getValue();
            Collections.sort(studentsWithGrades);
            for(Student s: studentsWithGrades){
                System.out.println(s);
            }
        }

        System.out.println("Repository");
        Repository<Integer,Student> studentRepository = new InMemoryRepository<>();
        List<Student> studentsList = getListStudents();
        for(Student s: studentsList){
            studentRepository.save(s);
        }

        for(Student s: studentRepository.findAll()){
            System.out.println(s);
        }
    }
}