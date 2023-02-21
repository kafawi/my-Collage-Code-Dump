package algo;

import java.util.LinkedList;
import java.util.List;

public class Quickersort extends Sort {

	@Override
	public void sort(List<Sortobject<?>> list) {
		resetCounter();
		List<Sortobject<?>> l = mysort(list);
		// System.err.println(l.get(0).getKey());
		list.clear();
		// list.addAll(l);
		list.addAll(l);
		// System.err.println(list.get(0).getKey());
	}

	public List<Sortobject<?>> mysort(List<Sortobject<?>> list) {
		List<Sortobject<?>> ergList = new LinkedList<>();
		for (Sortobject<?> s : list) {
			if (ergList.isEmpty()) {
				// Wenn die Liste leer ist, ...
				ergList.add(s);
			} else {
				// Ann�herung an den Listenplatz

				int i = ergList.size() / 2;
				int iAlt = i;
				int schritt = i;
				do {
					// counter++;
					iAlt = i;
					schritt = schritt / 2;
					if (compare(s.getKey(), ergList.get(i).getKey()) > 0) {
						i = i - schritt;
					} else {
						i = i + (schritt);
					}
				} while (Math.abs(i - iAlt) > 10);

				if (compare(s.getKey(), ergList.get(i).getKey()) >= 0) {
					// Wenn das einzusortierende Element >= dem
					// Listenplatz(i) ist, ...
					while (i < ergList.size()) {
						// counter++;
						if (compare(s.getKey(), ergList.get(i).getKey()) > 0) {
							i++;
						} else {
							break;
						}
					}
					if (i < ergList.size()) {
						// f�ge es an der passenden Stelle ein
						moveCount++;
						ergList.add(i, s);
					} else {
						// f�ge es hinten an
						moveCount++;
						ergList.add(s);
					}
				} else {
					// Wenn das einzusortierende Element < dem
					// Listenplatz(i) ist, ...
					while (i >= 0) {
						// counter++;
						if (compare(s.getKey(), ergList.get(i).getKey()) < 0) {
							i--;
						} else {
							i++;
							break;
						}
					}
					if (i < 0) {
						moveCount++;
						ergList.add(0, s);
					} else {
						moveCount++;
						ergList.add(i, s);
					}
				}
			}
		}
		return ergList;

	}

}
