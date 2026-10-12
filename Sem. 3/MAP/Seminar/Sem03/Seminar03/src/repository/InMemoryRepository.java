package repository;

import model.Student;

public class InMemoryRepository implements Repository<Integer, Student> {
    @Override
    public Student findOne(Integer integer) {
        return null;
    }

    @Override
    public Iterable<Student> findAll() {
        return null;
    }

    @Override
    public Student save(Student entity) {
        return null;
    }

    @Override
    public Student delete(Integer integer) {
        return null;
    }

    @Override
    public Student update(Student entity) {
        return null;
    }
}
