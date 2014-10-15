package test;

import java.util.Collection;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;

import test.Book;

public class BookDao {
    private static final BookDao instance;
    private static final ConcurrentMap<String, Book> data;
    
    static {
        instance = new BookDao();
        data = new ConcurrentHashMap<String, Book>();
        data.put("suirui", new Book("suirui", "Code Complete, Second Edition;publishdate: 2010-02-21;publisher: 机械工业出版社", 32.99));
        data.put("arrui", new Book("arrui", "The Art of Project Management;publishdate: 1999-06-21;publisher: 工大出版社", 35.96));
        data.put("wenrui", new Book("wenrui", "Design Patterns: Elements of Reusable Object-Oriented Software;publishdate: 2000-12-21;publisher: 人民出版社", 43.19));
        data.put("seler", new Book("seler", "Information Architecture for the World Wide Web: Designing Large-Scale Web Sites;publishdate: 2004-06-21;publisher: 高教出版社", 25.19));
        data.put("kerel", new Book("kerel", "Software Estimation: Demystifying the Black Art", 25.19));
    }
    
    private BookDao() {}
    
    public static BookDao getInstance() {
        return instance;
    }
    
    public Collection<Book> getBooks() {
        return data.values();
    }
    
    public Book getBook(String isbn) {
        return data.get(isbn);
    }
    
    public void storeBook(Book book) {
        data.put(book.getIsbn(), book);
    }
        
    public void removeBook(String isbn) {
        data.remove(isbn);
    }
    
    public void removeBooks(String[] isbns) {
        for(String isbn : isbns) {
            data.remove(isbn);
        }
    }
}