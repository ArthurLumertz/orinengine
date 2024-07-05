package net.orin.util.exception;

import net.orin.*;

public class OrinRuntimeException extends RuntimeException {

	private static final long serialVersionUID = 1L;
	
	public OrinRuntimeException(String msg) {
		super(msg);
		Orin.log.fatal("exception", msg);
	}

}
