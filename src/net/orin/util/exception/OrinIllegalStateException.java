package net.orin.util.exception;

import net.orin.*;

public class OrinIllegalStateException extends IllegalStateException {

	private static final long serialVersionUID = 1L;
	
	public OrinIllegalStateException(String msg) {
		super(msg);
		Orin.log.fatal("exception", msg);
	}

}
