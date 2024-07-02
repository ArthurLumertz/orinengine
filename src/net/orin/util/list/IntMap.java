package net.orin.util.list;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class IntMap<T> {

	private final HashMap<Integer, T> intMap = new HashMap<Integer, T>();

	public void put(int id, T t) {
		this.intMap.put(id, t);
	}

	public T get(int id) {
		return this.intMap.get(id);
	}

	public int findKey(T t, int notFound) {
		for (Map.Entry<Integer, T> entry : this.intMap.entrySet()) {
			if (entry.getValue().equals(t)) {
				return entry.getKey();
			}
		}
		return notFound;
	}

	public boolean containsKey(int id) {
		return this.intMap.containsKey(id);
	}

	public void remove(int id) {
		this.intMap.remove(id);
	}

	public int size() {
		return this.intMap.size();
	}

	public void clear() {
		this.intMap.clear();
	}

	public Set<Map.Entry<Integer, T>> entrySet() {
		return this.intMap.entrySet();
	}

	public Set<Integer> keySet() {
		return intMap.keySet();
	}

	public Collection<T> values() {
		return intMap.values();
	}
	
}
